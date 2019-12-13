/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** parser_main
*/

#include <string.h>
#include <stdlib.h>
#include "parse.h"
#include "replace.h"

char ***parse_cmd(const char *cmd)
{
    char *mcmd = strdup(cmd);
    char **cmds;
    char ***wcmds;

    perr(!mcmd, "malloc", NULL);
    while (mcmd != NULL && expand_backslash(mcmd) == true)
        mcmd = expand_on_backslach(mcmd);
    if (!mcmd)
        return NULL;
    cmds = get_cmds(mcmd);
    free(mcmd);
    if (!cmds)
        return NULL;
    wcmds = get_wcmds(cmds);
    return wcmds;
}
