/*
** EPITECH PROJECT, 2019
** prompt.c
** File description:
** choose between an interative prompt or a simple file read
*/

#include "prompt.h"

char *prompt(void)
{
    char *term = getenv("TERM");
    bool is_compatible = term != NULL &&
        (strcmp(term, "xterm") == 0 || strcmp(term, "xterm-256color") == 0);

    if (isatty(0)) {
        if (is_compatible) {
            print_prompt();
            return user_prompt();
        }
        dprintf(1, "$> ");
    }
    return get_next_line(0);
}
