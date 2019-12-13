/*
** EPITECH PROJECT, 2018
** window csfml
** File description:
** window csfml
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

static char *fill_new_var(char *name, char *value)
{
    char *new_var = NULL;
    int d = 0;

    new_var = init_new_var(value, name);
    if (new_var == NULL)
        return (NULL);
    for (size_t i = 0; i != (my_strlen(value) + my_strlen(name) + 1); i++) {
        if (i < my_strlen(name))
            new_var[i] = name[i];
        else if (i == my_strlen(name))
            new_var[i] = '\t';
        else {
            (value == NULL) ? 0 : (new_var[i] = value[d]);
            d++;
        }
    }
    return (new_var);
}

static int len_var(char **var)
{
    int i = 0;

    for (; var[i]; i++);
    return (i);
}

static int check_integrity(char *name)
{
    if (my_char_isalpha(name[0]) == 0) {
        write(2, "setvar: Variable name must begin with a letter.\n", 48);
        return (1);
    }
    if (my_str_isalphanum(name) == 0) {
        write(2, \
        "setvar: Variable name must contain alphanumeric characters.\n", 60);
        return (1);
    }
    return (0);
}

static char **set(char *name, char *value, int overwrite, char **var)
{
    int index = 0;
    int len_vare = len_var(var);

    if (name == NULL || var == NULL)
        return NULL;
    if (check_integrity(name) == 1)
        return (var);
    if (getvar(var, name, &index) != NULL) {
        if (overwrite == 1) {
            free(var[index]);
            var[index] = NULL;
            var[index] = fill_new_var(name, value);
        }
    } else {
        var = copy_var(var, 1);
        var[len_vare] = fill_new_var(name, value);
    }
    return (var);
}

char *gestion_var(char *key, char *value, int overwrite, cmd_t cmd)
{
    static char **var = NULL;
    char *return_get = NULL;

    if (var == NULL)
        var = init_var();
    switch (cmd) {
    case SET :
        var = set(key, value, overwrite, var);
        break;
    case UNSET :
        var = unset(key, var);
        break;
    case PRINT :
        printvar(var);
        break;
    case GET :
        return_get = getvar(var, key, NULL);
        break;
    }
    return return_get;
}
