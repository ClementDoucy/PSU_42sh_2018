/*
** EPITECH PROJECT, 2019
** echo.c
** File description:
** echo builtin
*/

#include "mysh.h"

void launch_echo(char *cmd, __attribute__((unused))char ***env, int *status)
{
    bool new_line = true;
    char **argv = launch_argv(cmd);

    if (!argv) {
        dprintf(2, "Error: malloc failed.\n");
        *status = 1;
        return;
    }
    if (argv[1] != NULL && strcmp(argv[1], "-n") == 0)
        new_line = false;
    for (int i = 1 + !new_line; argv[i]; i++)
        dprintf(1, (argv[i + 1] ? "%s " : "%s"), argv[i]);
    if (new_line == true)
        write(1, "\n", 1);
    destroy_2d_2allocs((void **)argv);
    *status = 0;
}