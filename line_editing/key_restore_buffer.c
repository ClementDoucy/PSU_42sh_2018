/*
** EPITECH PROJECT, 2019
** key_restore_buffer.c
** File description:
** restores the buffer
*/

#include "prompt.h"

void key_restore_buffer(line_t *line)
{
    char *buffer = buffer_copy(NULL, false);

    if (buffer == NULL)
        return;
    for (int i = 0; buffer[i]; i++) {
        line->str = add_char(line->str, buffer[i], line->cursor);
        line->cursor++;
        termcap(CURSOR_RIGHT);
    }
    reprint_prompt(line->str);
}
