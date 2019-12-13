/*
** EPITECH PROJECT, 2019
** user_prompt.c
** File description:
** interactive prompt
*/

#include "prompt.h"

char *user_prompt(void)
{
    static termios_t readable_termios;
    static termios_t old_termios;
    line_t *line = start_readline(&readable_termios, &old_termios);

    if (!line)
        return NULL;
    while (line->key != NEWLINE) {
        if (read(0, &line->key, 1) <= 0 || line->key == CTRL_D)
            return (finish_readline(line, false, &old_termios));
        if (line->key != NEWLINE)
            key_actions(line);
    }
    return (finish_readline(line, true, &old_termios));
}
