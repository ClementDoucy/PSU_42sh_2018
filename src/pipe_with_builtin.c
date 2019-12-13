/*
** EPITECH PROJECT, 2019
** pipe_with_builtin.c
** File description:
** manage pipe with bulitin
*/

#include "mysh.h"

extern const builtin_t builtins[];

bool is_builtin(char *cmd)
{
    if (are_eq_str(cmd, "env"))
        return true;
    for (int i = 0; i < 4; i++)
        if (are_eq_str(cmd, builtins[i].builtin))
            return true;
    return false;
}

void exec_last_pipe(char *cmd, char ***env, int *status, int *fd)
{
    if (!is_builtin(cmd)) {
        exec_pipe(cmd, *env, status, fd);
        return;
    }
    launch_cmd(cmd, env, status);
}

void last_redir_to_file(bin_str_t *node, char ***env, int *status, int *tmp)
{
    int fd = 0;

    if (!node || !node->right)
        return;
    if (check_right_redir(node->right->str, status))
        return;
    if (SUP(*node->str) && SUP(*(node->str + 1))) {
        last_append_redir_to_file(node, env, status, tmp);
        return;
    }
    if (access(node->right->str, F_OK))
        fd = open(node->right->str, O_WRONLY | O_CREAT,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    else
        fd = open(node->right->str, O_WRONLY | O_TRUNC);
    tmp[1] = dup(fd);
    my_close(&fd);
    exec_last_pipe(node->left->str, env, status, tmp);
    my_close(&(tmp[1]));
}

void last_append_redir_to_file(bin_str_t *node, char ***env,
    int *status, int *tmp)
{
    int fd = 0;

    if (access(node->right->str, F_OK))
        fd = open(node->right->str, O_WRONLY | O_CREAT,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    else
        fd = open(node->right->str, O_WRONLY | O_APPEND);
    tmp[1] = dup(fd);
    my_close(&fd);
    exec_last_pipe(node->left->str, env, status, tmp);
    my_close(&(tmp[1]));
}

void my_close(int *fd)
{
    if (fcntl(*fd, F_GETFL) != -1)
        close(*fd);
}