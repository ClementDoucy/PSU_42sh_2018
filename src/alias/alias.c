/*
** EPITECH PROJECT, 2019
** alias.c
** File description:
** alias
*/

#include "mysh.h"
#include "alias.h"

static bool is_alias_or_unalias_builtin(char *cmd)
{
    if (strncmp(cmd, "alias", 5) == 0 && (cmd[5] == ' ' || cmd[5] == 0))
        return true;
    else if (strncmp(cmd, "unalias", 7) == 0)
        return true;
    return false;
}

char *gestion_alias(char *cmd, int *status, char *name, cmd_t type)
{
    static char ***alias = NULL;
    size_t size = compute_size_argv(cmd);

    if (type == GET)
        return get_alias(alias, name);
    if (is_alias_or_unalias_builtin(cmd) == false)
        return NULL;
    if (!alias && !(alias = init_alias_tab_default()))
        return cmd;
    if (strncmp(cmd, "alias", 5) == 0)
        alias = alias_builtin(alias, cmd, size, status);
    else
        alias = unalias_builtin(alias, cmd, size, status);
    return cmd;
}
