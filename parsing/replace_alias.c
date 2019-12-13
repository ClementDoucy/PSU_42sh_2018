/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** replace_alias
*/

#include "mysh.h"
#include "parse.h"

char *replace_alias(char *word, int *status)
{
    char *tmp = word;
    int loop = 0;

    for (; loop < 100; loop++) {
        tmp = gestion_alias(NULL, status, word, GET);
        if (!tmp)
            return word;
        free(word);
        word = tmp;
    }
    if (loop == 100) {
        fprintf(stderr, "Alias loop.\n");
        *status = 1;
        return word;
    }
    return word;
}