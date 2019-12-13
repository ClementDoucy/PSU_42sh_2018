/*
** EPITECH PROJECT, 2018
** window csfml
** File description:
** window csfml
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

char *getvar(char **var, char *search, int *index)
{
    char *to_find = NULL;

    if (var == NULL || search == NULL)
        return NULL;
    for (int i = 0; var[i]; i++) {
        to_find = my_strstr(var[i], search);
        if (to_find != NULL) {
            to_find = my_strdup(&to_find[my_strlen(search) + 1]);
            (index == NULL) ? 0 : (*index = i);
            break;
        }
    }
    return (to_find);
}
