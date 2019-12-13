/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_cmds
*/

#include <stdlib.h>
#include <string.h>
#include "parse.h"

static char *dup_skip_zeros(char *cmd, size_t *len_cmd)
{
    size_t lendup = *len_cmd;
    char *mem = cmd;
    size_t i = 0;
    char *new = malloc(*len_cmd + 1);

    perr(!new, "malloc", NULL);
    for (; i < lendup && !(*cmd); i++, cmd++)
        *len_cmd -= 1;
    for (i = 0; i < *len_cmd; i++)
        new[i] = cmd[i];
    new[i] = '\0';
    free(mem);
    return new;
}

static char **cmd_to_cmds(char *cmd, size_t nb_of_cmds, size_t len_cmd)
{
    char **cmds = malloc(sizeof(char *) * (nb_of_cmds + 1));
    size_t j = 0;
    size_t i = 0;

    cmd = dup_skip_zeros(cmd, &len_cmd);
    perr(!cmd || !cmds, "malloc", NULL);
    for (; j < nb_of_cmds; j++) {
        for (; i < len_cmd && cmd[i] == '\0'; i++);
        cmds[j] = &(cmd[i]);
        for (; cmd[i]; i++);
    }
    cmds[nb_of_cmds] = NULL;
    return cmds;
}

char **get_cmds(const char *cmd)
{
    char *cmd_dup = strdup(cmd);
    size_t len_cmd = strlen(cmd_dup);
    int status = 0;
    size_t nb_of_cmds;
    char **cmds;

    perr(!cmd_dup, "strdup", NULL);
    nb_of_cmds = sepcmds(cmd_dup, &status);
    if (status != 0) {
        free(cmd_dup);
        return NULL;
    }
    cmds = cmd_to_cmds(cmd_dup, nb_of_cmds, len_cmd);
    return cmds;
}