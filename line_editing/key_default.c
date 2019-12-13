/*
** EPITECH PROJECT, 2019
** key_default.c
** File description:
** prints the non-special chars
*/

#include "prompt.h"

void key_default(line_t *line)
{
    if (line->cursor > strlen(line->str))
        return;
    line->str = add_char(line->str, line->key, line->cursor);
    line->cursor++;
    reprint_prompt(line->str);
    termcap(CURSOR_RIGHT);
}
