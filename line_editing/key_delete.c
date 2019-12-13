/*
** EPITECH PROJECT, 2019
** key_delete.c
** File description:
** handles the delete key
*/

#include "prompt.h"

void key_delete(line_t *line)
{
    if (line->cursor == 0)
        return;
    del_char(line->str, line->cursor);
    line->cursor--;
    reprint_prompt(line->str);
    termcap(CURSOR_LEFT);
}
