/*
** EPITECH PROJECT, 2019
** alias_add.c
** File description:
** add or modify the value of an alias
*/

#include "mysh.h"
#include "alias.h"

static char ***realloc_3d_str(char ***tab, size_t size)
{
    size_t i = 0;
    char ***new = NULL;

    for (i = 0; tab[i]; i++);
    if (!(new = malloc(sizeof(char **) * (i + size + 1))))
        return NULL;
    for (i = 0; tab[i]; i++) {
        if (!(new[i] = malloc(sizeof(char *) * 2)))
            return NULL;
        new[i][KEY] = my_strdup(tab[i][KEY]);
        new[i][VALUE] = my_strdup(tab[i][VALUE]);
        free(tab[i][KEY]);
        free(tab[i][VALUE]);
        free(tab[i]);
    }
    free(tab);
    new[i] = NULL;
    return new;
}

static char ***create_alias_first(char ***alias, char *key, char *value)
{
    if (!(alias[0] = malloc(sizeof(char *) * 2)))
        return NULL;
    alias[0][KEY] = my_strdup(key);
    alias[0][VALUE] = my_strdup(value);
    alias[1] = NULL;
    return alias;
}

size_t get_alias_nb(char ***alias)
{
    size_t nb = 0;

    while (alias[nb])
        nb++;
    return nb;
}

char ***add_alias(char ***alias, char *key, char *value)
{
    size_t n = get_alias_nb(alias) + 1;

    if (!alias)
        return NULL;
    if (!alias[0])
        return create_alias_first(alias, key, value);
    for (int i = 0; alias[i]; i++)
        if (strcmp(alias[i][KEY], key) == 0) {
            alias[i][VALUE] = my_strdup(value);
            if (!alias[i][VALUE])
                return NULL;
            return alias;
        }
    if ((!(alias = realloc_3d_str(alias, 1))) || \
            (!(alias[n - 1] = malloc(sizeof(char *) * 2))) || \
            !(alias[n - 1][0] = my_strdup(key)) || \
            !(alias[n - 1][1] = my_strdup(value)))
        return NULL;
    alias[n++] = NULL;
    alias = sort_alias(alias);
    return alias;
}

void destroy_alias(char ***alias)
{
    for (int i = 0; alias[i]; i++) {
        free(alias[i][KEY]);
        free(alias[i][VALUE]);
        free(alias[i]);
    }
    free(alias);
}
