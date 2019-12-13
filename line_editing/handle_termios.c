/*
** EPITECH PROJECT, 2019
** handle_termios.c
** File description:
** uncanonizes the terminal and resets it
*/

#include "prompt.h"

static bool unbuffer_term(termios_t *readable_termios, termios_t *old_termios)
{
    static bool attributes_saved = false;

    if (attributes_saved == false) {
        if (tgetent(NULL, getenv("TERM=")) == -1)
            return false;
        if (tcgetattr(0, readable_termios) == -1)
            return false;
        if (tcgetattr(0, old_termios) == -1)
            return false;
        readable_termios->c_lflag &= ~(ICANON | ECHO);
        attributes_saved = true;
    }
    if (tcsetattr(0, TCSANOW, readable_termios) == -1)
        return false;
    return true;
}

line_t *start_readline(termios_t *readable_termios, termios_t *old_termios)
{
    line_t *line = calloc(1, sizeof(line_t));

    if (line == NULL)
        return NULL;
    global_line(line, true);
    line->str = calloc(1, sizeof(char));
    if (!unbuffer_term(readable_termios, old_termios))
        return NULL;
    return line;
}

char *finish_readline(line_t *line, bool returning, termios_t *old_termios)
{
    char *save = NULL;

    if (returning)
        save = strdup(line->str);
    if (tcsetattr(0, TCSANOW, old_termios) == -1)
        return NULL;
    free(line->str);
    free(line);
    global_line(NULL, true);
    write(1, "\n", 1);
    return save;
}
