/*
** EPITECH PROJECT, 2019
** binary_tree.c
** File description:
** binary tree handling
*/

#include "mysh.h"

bin_str_t *init_bin_str(char *str)
{
    bin_str_t *node = malloc(sizeof(bin_str_t));

    if (!node)
        return NULL;
    node->str = str;
    node->left = NULL;
    node->right = NULL;
    return node;
}

bin_str_t *build_tree(char *cmd)
{
    bin_str_t *new = NULL;

    if (!*cmd)
        return NULL;
    if (!is_simple_command(cmd)) {
        if (!(new = init_bin_str(get_operator(cmd))))
            return NULL;
        if (!(new->left = init_bin_str(get_cmd(cmd))))
            return NULL;
    } else
        if (!(new = init_bin_str(get_cmd(cmd))))
            return NULL;
    for (; *cmd; cmd++)
        if (PIPE(*cmd) || SEMI(*cmd) || SUP(*cmd) || INF(*cmd))
            break;
    if ((SUP(*cmd) && SUP(*(cmd + 1))) || (INF(*cmd) && INF(*(cmd + 1))))
        cmd++;
    if (*cmd)
        cmd++;
    new->right = build_tree(cmd);
    return new;
}

void print_tree(bin_str_t *node)
{
    if (!node)
        return;
    print_tree(node->left);
    if (node->str)
        my_print(1, "str = [%s]\n", node->str);
    else
        my_print(1, "str = (null)\n");
    print_tree(node->right);
}

void destroy_tree(bin_str_t *node)
{
    if (!node)
        return;
    if (node->left) {
        if (node->left->str) {
            free(node->left->str);
            node->left->str = NULL;
        }
        free(node->left);
        node->left = NULL;
    }
    destroy_tree(node->right);
    if (node->str)
        free(node->str);
    free(node);
}

size_t pipe_len(bin_str_t *node)
{
    if (!node)
        return 0;
    if (!PIPE(*node->str) && !SUP(*node->str) && !INF(*node->str))
        pipe_len(node->right);
    else
        return pipe_len(node->right) + 1;
    return 0;
}
