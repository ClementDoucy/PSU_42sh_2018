/*
** EPITECH PROJECT, 2019
** pipe.c
** File description:
** manage pipe ('|')
*/

#include "mysh.h"

static const char *mlc_err = "Error: malloc failed. Can't parse commmand.";
static const char *inv_cmd = "Invalid null command.";

void manage_child(char *cmd, char **env)
{
    char *bin = NULL;
    char **argv = launch_argv(cmd);

    if (!argv)
        return;
    if (is_filepath(argv[0]))
        execve(argv[0], argv, env);
    else {
        bin = launch_bin(argv[0], env);
        if (bin) {
            execve(bin, argv, env);
            free(bin);
        }
    }
    check_child_error(argv[0]);
    destroy_2d_2allocs((void **)argv);
    exit(1);
}

void exec_pipe(char *cmd, char **env, int *status, int *fd)
{
    if (!fork()) {
        for (int i = 0; i < 2; i++)
            if (fd[i] != -1) {
                dup2(fd[i], i);
                my_close(&(fd[i]));
            }
        launch_cmd(cmd, &env, status);
        exit(*status);
    } else
        for (int i = 0; i < 2; i++)
            if (fd[i] != -1)
                my_close(&(fd[i]));
}

void manage_semi(char **cmd_arr, char ***env, int *status)
{
    char **arr = NULL;
    cond_oprt_t *cond_oprt = NULL;

    for (; *cmd_arr; cmd_arr++) {
        if (is_simple_command(*cmd_arr) && !is_empty_line(*cmd_arr))
            launch_cmd(*cmd_arr, env, status);
        else if (!is_empty_line(*cmd_arr)) {
            if (!(arr = sep_cond_oprt(*cmd_arr, &cond_oprt))) {
                my_puts_stderr(cond_oprt ? inv_cmd : mlc_err);
                *status = 1;
                return;
            }
            manage_conditionnal(arr, cond_oprt, env, status);
            if (cond_oprt) {
                free(cond_oprt);
                cond_oprt = NULL;
            }
            destroy_2d_tab((void **)arr);
        }
    }
}

int redir_from_file(bin_str_t *node, int *status)
{
    char *fp = NULL;
    int fd = 0;

    if (!node || !node->right || !INF(*node->str))
        return -1;
    if (PIPE(*node->right->str) || SUP(*node->right->str))
        fp = node->right->left->str;
    else
        fp = node->right->str;
    if (INF(*(node->str + 1)))
        return double_left_redir(fp);
    if (access(fp, F_OK)) {
        my_print(2, "%s: No such file or directory.\n", fp);
        *status = 1;
        return -2;
    } if ((fd = open(fp, O_RDONLY)) == -1) {
        my_print(2, "%s: Permission denied.\n", fp);
        *status = 1;
        return -2;
    }
    return dup(fd);
}

int double_left_redir(char *str)
{
    int fd[2];
    char *buff = NULL;
    size_t n = 0;

    pipe(fd);
    if (!fork()) {
        my_close(&(fd[0]));
        my_putstr("? ");
        while (getline(&buff, &n, stdin) != -1 && !my_strcmp(str, buff)) {
            my_print(fd[1], "%s\n", buff);
            my_putstr("? ");
        }
        free(buff);
        my_close(&(fd[1]));
        exit(0);
    } else {
        wait(NULL);
        my_close(&(fd[1]));
        return dup(*fd);
    }
    return 0;
}
