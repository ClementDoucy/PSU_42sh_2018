/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** sep_cond_oprt
*/

#include <ctype.h>
#include "mysh.h"

static const char *STRAND = "&&";
static const char *STROR = "||";

char *skip(char *cmd)
{
    switch (*cmd) {
        case '"':
            for (cmd++; *cmd && *cmd != '"'; cmd++);
            break;
        case '\'':
            for (cmd++; *cmd && *cmd != '\''; cmd++);
            break;
        case '`':
            for (cmd++; *cmd && *cmd != '`'; cmd++);
            break;
        case '(':
            for (cmd++; *cmd && *cmd != ')'; cmd++);
            break;
    }
    return cmd;
}

static int split_gesture(char **cmd, cond_oprt_t **st, size_t *i)
{
    size_t and = strncmp(*cmd, STRAND, 2);
    size_t or = strncmp(*cmd, STROR, 2);

    if (!and || !or) {
        *st = realloc(*st, sizeof(cond_oprt_t) * (*i + 1));
        if (!(*st))
            return 84;
        (*st)[*i] = END_COND_OPRT;
        (*st)[*i - 1] = (and == 0) ? (AND) : (OR);
        *i += 1;
        *cmd = strncpy(*cmd, "\0\0", 2);
        *cmd += 2;
        for (; **cmd && isspace(**cmd); (*cmd)++);
        if (**cmd == '\0')
            return 84;
    }
    return 0;
}

static char **append_line(char **arr, char *line)
{
    size_t len = 0;

    for (; arr && arr[len]; len++);
    arr = realloc(arr, sizeof(char *) * (len + 2));
    if (!arr)
        return NULL;
    arr[len] = line;
    arr[len + 1] = NULL;
    return arr;
}

static char **split_at_zeros(char **cmd, cond_oprt_t *state)
{
    char **new = NULL;
    char *line;
    size_t len;

    for (size_t i = 0; state; i++) {
        len = strlen(*cmd);
        line = malloc(sizeof(char) * (len + 1));
        if (!line)
            return NULL;
        line = strncpy(line, *cmd, len + 1);
        new = append_line(new, line);
        if (!new)
            return NULL;
        *cmd += len + 2;
        if (state[i] == END_COND_OPRT)
            break;
    }
    return new;
}

char **sep_cond_oprt(char *cmd, cond_oprt_t **state)
{
    char *mem = cmd;
    size_t i = 1;
    char **new = NULL;

    *state = malloc(sizeof(cond_oprt_t));
    if (!state)
        return NULL;
    *state[0] = END_COND_OPRT;
    for (; *cmd != '\0'; (*cmd ? cmd++ : 0)) {
        if (*cmd == '\\') {
            cmd++;
            continue;
        }
        cmd = skip(cmd);
        if (split_gesture(&cmd, state, &i) == 84)
            return NULL;
    }
    new = split_at_zeros(&mem, *state);
    return new;
}
