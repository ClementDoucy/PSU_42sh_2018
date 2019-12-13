/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** delete_cmd
*/

#include <stdlib.h>

void delete_cmds(char **cmds)
{
    free(*cmds);
    free(cmds);
}

void delete_word_cmd(char **wcmd)
{
    for (size_t i = 0; wcmd[i] != NULL; i++)
        free(wcmd[i]);
    free(wcmd);
}

void delete_wcmds(char ***wcmds)
{
    if (!wcmds)
        return;
    for (size_t i = 0; wcmds[i] != NULL; i++)
        delete_word_cmd(wcmds[i]);
    free(wcmds);
}