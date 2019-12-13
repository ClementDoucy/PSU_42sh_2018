/*
** EPITECH PROJECT, 2018
** window csfml
** File description:
** window csfml
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

int my_count_tab(char **var_ini)
{
    int i = 0;

    if (var_ini == NULL)
        return 0;
    for (; var_ini[i]; i++);
    return (i);
}

static char **alloc_var(char **var_ini, int add)
{
    int nb_line = my_count_tab(var_ini) + add;
    char **var = NULL;

    if ((var = malloc(sizeof(char *) * (nb_line + 1))) == NULL)
        exit(84);
    var[nb_line] = NULL;
    for (int i = 0; i != (nb_line - add); i++) {
        var[i] = malloc(sizeof(char) * (my_strlen(var_ini[i]) + 1));
        var[i][my_strlen(var_ini[i])] = '\0';
    }
    return (var);
}

void clean_var(char **var)
{
    for (int i = 0; var[i]; i++)
        free(var[i]);
    free(var);
}

char **copy_var(char **var_ini, int add)
{
    char **var = alloc_var(var_ini, add);

    for (int i = 0; var_ini[i]; i++) {
        for (int d = 0; var_ini[i][d]; d++)
            var[i][d] = var_ini[i][d];
    }
    return (var);
}
