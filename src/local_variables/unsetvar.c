/*
** EPITECH PROJECT, 2018
** window csfml
** File description:
** window csfml
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

static char **alloc_unset(char **var_ini, int index, int nb_line)
{
    char **var = NULL;
    int d = 0;

    if ((var = malloc(sizeof(char *) * (nb_line + 1))) == NULL)
        exit(84);
    for (int i = 0; var_ini[i]; i++) {
        if (i != index) {
            var[d] = malloc(sizeof(char) * (my_strlen(var_ini[i]) + 1));
            var[d][my_strlen(var_ini[i])] = '\0';
            d++;
        }
    }
    var[d] = NULL;
    return (var);
}

static char **copy_unset(char **var, int index)
{
    int a = 0;
    int nb_line = my_count_tab(var) - 1;
    char **new_var = alloc_unset(var, index, nb_line);

    for (int i = 0; var[i]; i++) {
        if (i != index) {
            for (int d = 0; var[i][d]; d++)
                new_var[a][d] = var[i][d];
            a++;
        }
    }
    clean_var(var);
    var = NULL;
    return (new_var);
}

char **unset(char *name, char **var)
{
    static char **new_var = NULL;
    int index = 0;
    static int check = 0;

    if (name == NULL || var == NULL)
        return (NULL);
    if (check == 0)
        new_var = var;
    if (getvar(var, name, &index) != NULL) {
        new_var = copy_unset(var, index);
        check = 1;
        return (new_var);
    }
    return (new_var);
}
