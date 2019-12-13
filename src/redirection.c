/*
** EPITECH PROJECT, 2019
** redirection.c
** File description:
** manage redirection
*/

#include "mysh.h"

void exec_all(bin_str_t *root, char ***env, int *status)
{
    size_t size = pipe_len(root);
    int fd[2 * size];
    int tmp = 0;

    if (!size || check_file_redir_error(root, status))
        return;
    if (check_input_redir_error(root->right, status))
        return;
    for (size_t k = 0; k < 2 * size; k++)
        fd[k] = -1;
    *status = 0;
    run_pipe(root, env, status, fd);
    tmp = *status;
    for (size_t i = 0; i < size + 1; i++) {
        wait(status);
        *status = WEXITSTATUS(*status);
        if (*status)
            tmp = *status;
    }
    *status = tmp;
}

void run_pipe(bin_str_t *node, char ***env, int *status, int *fd)
{
    int tmp[2];
    int i = 0;
    bin_str_t *save = node;

    if (!(node = start_redirection(node, status, &tmp[0])))
        return;
    for (; node->right && !(SUP(*node->str)); node = node->right, i += 2) {
        if (!INF(*save->str)) {
            pipe(fd + i);
            tmp[1] = dup(fd[i + 1]);
            exec_pipe(node->left->str, *env, status, tmp);
            i ? my_close(&(fd[i - 2])) : 0;
            tmp[0] = dup(fd[i]);
            my_close(&(fd[i + 1]));
        }
        save = node;
    }
    end_redir((bin_str_t *[]){node, save}, get_case(node, save),
    tmp, (shell_t){env, status});
}

void redir_to_file(bin_str_t *node, char **env, int *status, int *tmp)
{
    int fd = 0;

    if (check_right_redir(node->right->str, status))
        return;
    if (SUP(*node->str) && SUP(*(node->str + 1))) {
        append_redir_to_file(node, env, status, tmp);
        return;
    }
    if (access(node->right->str, F_OK))
        fd = open(node->right->str, O_WRONLY | O_CREAT,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    else
        fd = open(node->right->str, O_WRONLY | O_TRUNC);
    tmp[1] = dup(fd);
    my_close(&fd);
    exec_pipe(node->left->str, env, status, tmp);
    my_close(&(tmp[1]));
}

bool check_right_redir(char *file_path, int *status)
{
    if (access(file_path, F_OK))
        return false;
    if (!is_file_or_dir(file_path)) {
        my_print(2, "%s: Is a directory.\n", file_path);
        *status = 1;
        return true;
    }
    if (access(file_path, W_OK)) {
        my_print(2, "%s: Permission denied.\n", file_path);
        *status = 1;
        return true;
    }
    return false;
}

void append_redir_to_file(bin_str_t *node, char **env, int *status, int *tmp)
{
    int fd = 0;

    if (access(node->right->str, F_OK))
        fd = open(node->right->str, O_WRONLY | O_CREAT,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    else
        fd = open(node->right->str, O_WRONLY | O_APPEND);
    tmp[1] = dup(fd);
    my_close(&fd);
    exec_pipe(node->left->str, env, status, tmp);
    my_close(&(tmp[1]));
}
