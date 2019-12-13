/*
** EPITECH PROJECT, 2018
** window csfml
** File description:
** window csfml
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

char **init_var(void)
{
    char **var = malloc(sizeof(char *) * 2);

    if (var == NULL)
        exit(84);
    var[1] = NULL;
    var[0] = my_strdup("VAR_NAME\tlocal_variables");
    return (var);
}
