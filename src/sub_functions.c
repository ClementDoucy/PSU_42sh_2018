/*
** EPITECH PROJECT, 2019
** sub_functions.c
** File description:
** contains sub functions
*/

#include "mysh.h"

void get_old_pwd(char **pwd, char **old_pwd)
{
    if (!*pwd)
        return;
    if (*old_pwd)
        free(*old_pwd);
    *old_pwd = my_strdup(*pwd);
    free(*pwd);
}

bool is_path_valid_2(char **argv, char *home_path, char *old_pwd)
{
    if (are_eq_str(argv[1], "home"))
        if (!home_path || access(home_path, R_OK | W_OK | X_OK)) {
            destroy_2d_2allocs((void **)argv);
            return false;
        }
    if (are_eq_str(argv[1], "-"))
        if (!old_pwd) {
            destroy_2d_2allocs((void **)argv);
            return false;
        }
    return true;
}

bin_str_t *start_redirection(bin_str_t *node, int *status, int *fd)
{
    *fd = redir_from_file(node, status);
    if (*fd == -2) {
        *fd = -1;
        if (!node->right->right)
            return NULL;
        return node->right;
    }
    return node;
}

int get_case(bin_str_t *node, bin_str_t *save)
{
    if (!SUP(*node->str) && !INF(*save->str))
        return 0;
    if (!INF(*save->str))
        return 1;
    if (INF(*save->str) && SUP(*node->str))
        return 2;
    return 3;
}

void end_redir(bin_str_t **nodes, int opt, int *tmp, shell_t var)
{
    tmp[1] = -1;
    switch (opt)
    {
    case 0:
        exec_last_pipe((nodes[0])->str, var.env, var.status, tmp);
        break;
    case 1:
        last_redir_to_file(nodes[0], var.env, var.status, tmp);
        break;
    case 2:
        my_str_swap(&((nodes[1])->left->str), &((nodes[0])->left->str));
        last_redir_to_file(nodes[0], var.env, var.status, tmp);
        break;
    case 3:
        exec_last_pipe((nodes[1])->left->str, var.env, var.status, tmp);
        break;
    }
}
