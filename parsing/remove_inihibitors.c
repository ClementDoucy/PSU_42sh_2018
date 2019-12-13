/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** remove_inihibitors
*/

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "replace.h"

static char *remove_double_quotes(char *word)
{
    *word = '\0';
    for (word++; *word != '\0'; (*word) ? word++ : word) {
        skip_esc(word);
        if (*word == '"') {
            *word = '\0';
            break;
        }
    }
    return word;
}

static char *remove_single_quotes(char *word)
{
    *word = '\0';
    for (word++; *word != '\0'; (*word) ? word++ : word) {
        if (*word == '\'') {
            *word = '\0';
            break;
        }
    }
    return word;
}

static char *strcpy_strip_inhibitors(char *word, size_t len)
{
    char *new = malloc(sizeof(char) * (len + 1));
    size_t j = 0;

    if (!new || !word)
        return NULL;
    for (size_t i = 0; i < len; i++) {
        if (word[i] != '\0')
            new[j++] = word[i];
    }
    new[j] = '\0';
    free(word);
    return new;
}

char *remove_inhibitors(char *word, int *status __attribute__((unused)))
{
    char *mem = word;
    size_t len = strlen(word);

    for (size_t i = 0; i < len; (*word != '\0') ? word++ : word, i++) {
        skip_esc(word);
        if (*word == '\'')
            word = remove_single_quotes(word);
        if (*word == '"')
            word = remove_double_quotes(word);
    }
    return strcpy_strip_inhibitors(mem, len);
}