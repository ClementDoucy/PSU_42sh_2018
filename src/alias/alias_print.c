/*
** EPITECH PROJECT, 2019
** alias_print.c
** File description:
** print the list of alias of just the value of one given alias
*/

#include "mysh.h"
#include "alias.h"

void print_alias_tab(char ***alias)
{
    if (!alias)
        return;
    for (int i = 0; alias[i]; i++)
        printf("%s\t%s\n", alias[i][KEY], alias[i][VALUE]);
}

void print_alias_simple(char ***alias, const char *key)
{
    if (!alias)
        return;
    for (int i = 0; alias[i]; i++)
        if (!strcmp(alias[i][KEY], key))
            printf("%s\n", alias[i][VALUE]);
}
