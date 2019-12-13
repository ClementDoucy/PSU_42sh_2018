/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** preprocess_wcmd
*/

#include <stdlib.h>
#include "parse.h"

char *dup_word(char *start, char *end)
{
    size_t len = end - start;
    char *word = malloc(sizeof(char) * (len + 1));

    perr(!word, "malloc", NULL);
    word[len] = '\0';
    for (size_t i = 0; i < len; i++)
        word[i] = start[i];
    return word;
}