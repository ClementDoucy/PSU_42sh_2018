/*
** EPITECH PROJECT, 2019
** key_goto.c
** File description:
** gets to the ends of the line
*/

#include "prompt.h"

void key_goto_head(line_t *line)
{
    for (; line->cursor > 0; line->cursor--)
        termcap(CURSOR_LEFT);
}

void key_goto_tail(line_t *line)
{
    for (size_t len = strlen(line->str); line->cursor < len; line->cursor++)
        termcap(CURSOR_RIGHT);
}
