/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_word
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"

static char *get_end_of_op(char *start, size_t *endw)
{
    const char *op = which_op(start);
    size_t len = strlen(op);

    *endw += len;
    return start + len;
}

static char *get_end_of_word(char *start, size_t *endw, int *status)
{
    char *end = start;

    while (*end && !isspace(*end) && !is_op(end)) {
        end = skip_quotes(end, endw, status);
        end = skip_any(end, endw);
    }
    return end;
}

static char *get_word_in_cmd(char *cmd, size_t *endw, int *status)
{
    char *start = &cmd[*endw];
    char *word;
    char *end;

    if (is_op(start)) {
        end = get_end_of_op(start, endw);
    } else {
        end = get_end_of_word(start, endw, status);
    }
    if (*status != 0)
        return NULL;
    word = dup_word(start, end);
    if (!word)
        *status = 1;
    return word;
}

char *get_word(char *cmd, size_t *endw, int *status)
{
    char *new = preprocess_wcmd(cmd, endw);

    if (*new == '\0')
        return NULL;
    return get_word_in_cmd(cmd, endw, status);
}