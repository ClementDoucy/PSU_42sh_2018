/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** op
*/

#include <stdbool.h>
#include <string.h>

static const char *OP[] =
{
    "<", "<<", ">", ">>", "|", "&", "&&", "||", ")", "(", ";", NULL
};

const char *which_op(char *start)
{
    const char *mem = NULL;
    size_t len = 0;

    for (size_t i = 0; OP[i] != NULL; i++) {
        len = strlen(OP[i]);
        if (strncmp(start, OP[i], len) == 0)
            mem = OP[i];
    }
    return mem;
}

bool is_op(char *start)
{
    bool is_op = which_op(start) != NULL;

    return is_op;
}
