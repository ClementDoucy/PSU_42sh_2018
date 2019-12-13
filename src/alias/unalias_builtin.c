/*
** EPITECH PROJECT, 2019
** unalias_builtin.c
** File description:
** unalias
*/

#include "mysh.h"
#include "alias.h"

static char ***remove_alias(char ***alias, char *name)
{
    size_t nb = get_alias_nb(alias);
    char ***new = NULL;
    int i = 0;
    int j = 0;

    if (!(new = malloc(sizeof(char **) * (nb + 1))))
        return NULL;
    for (i = 0; alias[i]; i++) {
        if (strcmp(alias[i][KEY], name) == 0)
            continue;
        if (!(new[j] = malloc(sizeof(char *) * 2)))
            return NULL;
        new[j][KEY] = my_strdup(alias[i][KEY]);
        new[j++][VALUE] = my_strdup(alias[i][VALUE]);
        free(alias[i][KEY]);
        free(alias[i][VALUE]);
        free(alias[i]);
    }
    free(alias);
    new[j] = NULL;
    return new;
}

static char ***unalias_no_arg(char ***alias, int *status)
{
    printf("unalias: Too few arguments.\n");
    *status = 1;
    return alias;
}

static char ***unalias_with_args(char ***alias, char *cmd, int *status)
{
    char **args = NULL;

    args = str_to_word_array(cmd, " ");
    for (int i = 0; args[i]; i++)
        for (int j = 0; alias[j]; j++)
            if (strcmp(alias[j][0], args[i]) == 0)
                alias = remove_alias(alias, args[i]);
    *status = 0;
    return alias;
}

char ***unalias_builtin(char ***alias, char *cmd, size_t size, int *status)
{
    if (size == 1)
        return unalias_no_arg(alias, status);
    if (size >= 2)
        return unalias_with_args(alias, cmd, status);
    *status = 1;
    return alias;
}
