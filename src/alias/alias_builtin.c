/*
** EPITECH PROJECT, 2019
** alias.c
** File description:
** alias
*/

#include "mysh.h"
#include "alias.h"

static char ***alias_3_more_modify_or_add(char ***alias, char *cmd, size_t size)
{
    char *argv[2] = {0};

    argv[KEY] = get_alias_from_argv(cmd, KEY);
    if (size == 3)
        argv[VALUE] = get_alias_from_argv(cmd, VALUE);
    else
        argv[VALUE] = get_alias_from_argv_more_3_arguments(cmd, size);
    alias = add_alias(alias, argv[KEY], argv[VALUE]);
    return alias;
}

static void alias_2_arg_display_value(char ***alias, char *cmd)
{
    char *argv = NULL;

    if (!(argv = get_alias_from_argv(cmd, KEY)))
        return;
    print_alias_simple(alias, argv);
}

static void alias_no_arg_display_list(char ***alias)
{
    print_alias_tab(alias);
}

char ***alias_builtin(char ***alias, char *cmd, size_t size, int *status)
{
    if (size == 1)
        alias_no_arg_display_list(alias);
    if (size == 2)
        alias_2_arg_display_value(alias, cmd);
    if (size >= 3)
        alias = alias_3_more_modify_or_add(alias, cmd, size);
    *status = 0;
    return alias;
}
