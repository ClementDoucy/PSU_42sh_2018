/*
** EPITECH PROJECT, 2019
** clear_term.c
** File description:
** clears the screen
*/

#include "prompt.h"
#include "tools.h"

void clear_term(line_t *line)
{
    termcap(TERM_CLEAR);
    print_prompt();
    my_putstr(line->str);
    for (size_t i = 0; i < my_strlen(line->str) - line->cursor; i++)
        termcap(CURSOR_LEFT);
}
