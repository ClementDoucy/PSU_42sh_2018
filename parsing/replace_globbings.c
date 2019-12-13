/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** replace_globbings
*/

#include <glob.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse.h"

static char **arr_to_arr(char **g, size_t ac, char ***cmd, char *insert)
{
    char **new = malloc(sizeof(char *) * (ac + arrlen(*cmd) + 1));
    size_t j = 0;

    perr(!new, "malloc", NULL);
    for (size_t i = 0; (*cmd)[i] != NULL;) {
        if ((*cmd)[i] != insert) {
            new[j++] = (*cmd)[i++];
            continue;
        }
        i++;
        for (size_t k = 0; k < ac; k++) {
            new[j++] = strdup(g[k]);
            perr(!new[j - 1], "malloc", NULL);
        }
    }
    new[j] = NULL;
    return new;
}

static void process_status(int g_status, int *status)
{
    if (g_status == GLOB_NOSPACE || g_status == GLOB_ABORTED) {
        perror("glob");
        *status = 1;
    }
}

void replace_globbings(char ***cmd, char *word, int *status, size_t *i)
{
    glob_t g;
    int g_status;

    g_status = glob(word, GLOB_BRACE, NULL, &g);
    if (g_status != 0) {
        process_status(g_status, status);
        return;
    }
    if (g.gl_pathc > 0) {
        *cmd = arr_to_arr(g.gl_pathv, g.gl_pathc, cmd, word);
        free(word);
        *i += g.gl_pathc;
    }
    if (!(*cmd))
        *status = 1;
    globfree(&g);
}
