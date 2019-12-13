/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** skip
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"

char *skip_spaces(char *str)
{
    while (isspace(*str))
        str++;
    return str;
}

char *skip_any(char *str, size_t *endw)
{
    char *end = str;

    if (*str == ESC) {
        end++;
        (*endw) += 1;
    }
    if (*end) {
        end++;
        (*endw) += 1;
    }
    return end;
}

char *skip_quotes(char *str, size_t *endw, int *status)
{
    char *end = str;
    char end_of_quote = *str;

    if (!(*str) || strchr("\"'`", *str) == NULL)
        return end;
    do {
        end++;
        *endw += 1;
    } while (*end && (*end != end_of_quote));
    if (*end == '\0') {
        *status = 1;
        fprintf(stderr, "Unmatched '%c'.\n", end_of_quote);
    }
    return end;
}