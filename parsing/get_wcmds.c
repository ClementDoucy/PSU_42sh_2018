/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_wcmds
*/

#include <stdlib.h>
#include "parse.h"

char *preprocess_wcmd(char *cmd, size_t *endw)
{
    char *start = &cmd[*endw];
    char *new = skip_spaces(start);

    *endw += new - start;
    return new;
}

char **get_word_cmd(char *cmd)
{
    char **wcmd = NULL;
    size_t size = 1;
    int status = 0;

    cmd = skip_spaces(cmd);
    for (size_t endw = 0; cmd[endw] != '\0'; size++) {
        wcmd = realloc(wcmd, sizeof(char *) * (size + 1));
        wcmd[size - 1] = get_word(cmd, &endw, &status);
        wcmd[size] = NULL;
        if (status != 0) {
            free(wcmd);
            return NULL;
        }
    }
    return wcmd;
}

char ***get_wcmds(char **cmds)
{
    size_t len = arrlen(cmds);
    char ***wcmds = malloc(sizeof(char **) * (len + 1));

    perr(!wcmds, "malloc", NULL);
    wcmds[len] = NULL;
    for (size_t i = 0; cmds[i] != NULL; i++) {
        wcmds[i] = get_word_cmd(cmds[i]);
        if (!(wcmds[i])) {
            free(wcmds);
            delete_cmds(cmds);
            return NULL;
        }
    }
    delete_cmds(cmds);
    return wcmds;
}