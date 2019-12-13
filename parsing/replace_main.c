/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** replace_main
*/

#include <stdlib.h>
#include "replace.h"
#include "parse.h"

void replace_words_in_wcmd(char **wcmd, int *status)
{
    if (wcmd) {
        return;
    } else if (*status) {
        return;
    }
}

char ***replace_special_words(char ***wcmds)
{
    int status = 0;

    for (size_t i = 0; wcmds[i] != NULL; i++) {
        replace_words_in_wcmd(wcmds[i], &status);
        if (status != 0) {
            delete_wcmds(wcmds);
            return NULL;
        }
    }
    return wcmds;
}
