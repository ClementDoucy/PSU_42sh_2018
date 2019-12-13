/*
** EPITECH PROJECT, 2019
** alias_init.c
** File description:
** Init the alias tab per default
*/

#include "mysh.h"
#include "alias.h"

char ***init_alias_tab_default(void)
{
    char ***alias = malloc(sizeof(char **) * 2);

    if (!alias)
        return NULL;
    alias[0] = NULL;
    return alias;
}
