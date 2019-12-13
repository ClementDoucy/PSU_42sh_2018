/*
** EPITECH PROJECT, 2019
** get_alias.c
** File description:
** get alias value, whether from the given command of from the existing list
*/

#include "mysh.h"
#include "alias.h"

char *get_alias_from_argv(char *cmd, int state)
{
    int i = strlen("alias");
    char *argv = NULL;

    while (i == ' ')
        i++;
    if (!(argv = my_strdup(&cmd[++i])))
        return NULL;
    i = 0;
    while (argv[i] != ' ' && argv[i])
        i++;
    if (state == KEY) {
        argv[i] = 0;
        return argv;
    }
    return &(argv[++i]);
}

char *get_alias_from_argv_more_3_arguments(char *cmd, size_t size)
{
    char **argv = get_argv(cmd, size);
    char *value = NULL;
    int size_to_alloc = 2;
    int p = 1;

    if (!argv)
        return NULL;
    for (int i = 1; argv[i]; i++)
        size_to_alloc += strlen(argv[i]);
    if (!(value = malloc(sizeof(char) * (size_to_alloc + size + 1))))
        return NULL;
    value[0] = '(';
    for (int i = 2; argv[i]; i++) {
        for (int j = 0; argv[i][j]; j++)
            value[p++] = argv[i][j];
        if (argv[i + 1])
            value[p++] = ' ';
    }
    value[p++] = ')';
    value[p] = 0;
    return value;
}
