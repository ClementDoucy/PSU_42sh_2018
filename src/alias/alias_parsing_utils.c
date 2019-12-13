/*
** EPITECH PROJECT, 2019
** alias_parsing_utils.c
** File description:
** two functions utils to replace aliases in cmd entered by user
*/

#include "mysh.h"
#include "alias.h"

bool is_alias(char ***alias, const char *name)
{
    for (int i = 0; alias[i]; i++)
        if (!strcmp(alias[i][KEY], name))
            return true;
    return false;
}

char *get_alias(char ***alias, const char *name)
{
    if (!alias || !name)
        return NULL;
    for (int i = 0; alias[i]; i++)
        if (!strcmp(alias[i][KEY], name))
            return alias[i][VALUE];
    return NULL;
}
