/*
** EPITECH PROJECT, 2019
** binary_research.c
** File description:
** search binary in path
*/

#include "mysh.h"

char *launch_research(char *cmd, char **bin_path)
{
    char *binary = NULL;
    char *tmp = NULL;
    int i = 0;

    if (cmd[0] == '.' && cmd[1] == '/')
        return NULL;
    for (; bin_path && bin_path[i] && !binary; i++) {
        tmp = my_strcat(bin_path[i], "/");
        tmp = my_strcat(tmp, cmd);
        if (!access(tmp, X_OK))
            binary = my_strdup(tmp);
        free(tmp);
    }
    return binary;
}
