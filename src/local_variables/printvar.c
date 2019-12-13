/*
** EPITECH PROJECT, 2018
** window csfml
** File description:
** window csfml
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

char *init_new_var(char *value, char *name)
{
    char *new_var = NULL;

    if (value != NULL) {
        new_var = malloc(sizeof(char) * (my_strlen(value) +
        my_strlen(name) + 2));
        new_var[(my_strlen(value) + my_strlen(name) + 1)] = '\0';
    } else {
        new_var = malloc(sizeof(char) * (my_strlen(value) +
        my_strlen(name) + 2));
        new_var[my_strlen(name) + 1] = '\0';
    }
    return (new_var);
}

void printvar(char **var)
{
    for (int i = 1; var[i]; i++)
        my_print(1, "%s\n", var[i]);
}
