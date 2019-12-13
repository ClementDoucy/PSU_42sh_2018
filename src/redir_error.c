/*
** EPITECH PROJECT, 2019
** redir_error.c
** File description:
** error management for redirection
*/

#include "mysh.h"

bool check_redir_error(char *cmd)
{
    char *str = str_clean(cmd);
    char last = 0;

    if (!str)
        return true;
    if (str[my_strlen(str) - 1] == '\n')
        str[my_strlen(str) - 1] = '\0';
    last = str[my_strlen(str) - 1];
    free(str);
    if (PIPE(last)) {
        my_puts_stderr("Invalid null command.");
        return true;
    }
    if (SUP(last) || INF(last)) {
        my_puts_stderr("Missing name for redirect.");
        return true;
    }
    if (check_operator_error(cmd))
        return true;
    return false;
}

bool check_file_redir_error(bin_str_t *node, int *status)
{
    if (!node->right)
        return false;
    if (SUP(*node->left->str) ||
        PIPE(*node->left->str) || INF(*node->left->str)) {
        *status = 1;
        my_puts_stderr("Invalid null command.");
        return true;
    }
    if (SUP(*node->str) && node->right->right) {
        *status = 1;
        my_puts_stderr("Ambiguous output redirect.");
        return true;
    }
    return check_file_redir_error(node->right, status);
}

bool check_input_redir_error(bin_str_t *node, int *status)
{
    if (!node || !node->right)
        return false;
    if (INF(*node->str)) {
        *status = 1;
        my_puts_stderr("Ambiguous output redirect.");
        return true;
    }
    return check_input_redir_error(node->right, status);
}

bool check_operator_error(char *cmd)
{
    char **argv = launch_argv(cmd);

    if (!argv)
        return true;
    for (int i = 0; argv[i + 1]; i++) {
        if ((PIPE(argv[i][0]) || SUP(argv[i][0]) || INF(argv[i][0])) &&
            (PIPE(argv[i + 1][0]) || SUP(argv[i + 1][0]) ||
            INF(argv[i + 1][0]))) {
            my_puts_stderr("Missing name for redirect.");
            return true;
        }
    }
    return false;
}
