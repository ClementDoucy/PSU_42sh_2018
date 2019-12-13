/*
** EPITECH PROJECT, 2019
** global_line.c
** File description:
** handles the sigint signal by erasing the buffer
*/

#include "prompt.h"

line_t *global_line(line_t *new_line, bool set)
{
    static line_t *line = NULL;

    if (set)
        line = new_line;
    return line;
}

void catch_sigint(int sig)
{
    line_t *line = NULL;

    if (sig == SIGINT) {
        line = global_line(NULL, false);
        if (line == NULL) {
            dprintf(1, "\b\b  \n$> ");
            return;
        }
        free(line->str);
        line->str = calloc(1, sizeof(char));
        line->cursor = 0;
        write(1, "\n", 1);
        print_prompt();
        my_putstr(line->str);
    }
}
