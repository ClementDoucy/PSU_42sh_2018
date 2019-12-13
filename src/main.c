/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main for minishell
*/

#include "mysh.h"

int main(__attribute__((unused))int ac, __attribute__((unused))char **av,
    char **env)
{
    char **env_cpy = NULL;

    env_cpy = str_2d_dup(env);
    if (!env) {
        my_puts_stderr("Error: environnement duplication failed.\n");
        return 84;
    }
    launch(env_cpy);
    return 0;
}
