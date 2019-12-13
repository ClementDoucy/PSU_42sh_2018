/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** append_on_backslash
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool expand_backslash(char *str)
{
    size_t len = strlen(str);

    if (len != 0)
        return (str[len - 1] == '\\');
    return false;
}

static char *strmerge(char *str1, char *str2)
{
    size_t lens = strlen(str1) + strlen(str2);
    char *merge = malloc(sizeof(char) * (lens + 1));

    if (!merge)
        return NULL;
    merge = strcpy(merge, str1);
    merge = strcat(merge, str2);
    merge[lens] = 0;
    return merge;
}

char *expand_on_backslach(char *cmd)
{
    char *mem = cmd;
    size_t last = strlen(cmd) - 1;
    size_t size = 0;
    char *append = NULL;

    printf("> ");
    if (getline(&append, &size, stdin) == -1) {
        if (append != NULL)
            free(append);
        return NULL;
    }
    cmd[last] = '\0';
    if (*append)
        append[strlen(append) - 1] = '\0';
    cmd = strmerge(cmd, append);
    free(mem);
    free(append);
    return cmd;
}
