/*
** EPITECH PROJECT, 2019
** key_suppr.c
** File description:
** handles the suppr key
*/

#include "prompt.h"

void key_suppr(line_t *line)
{
    char c = 0;

    read(0, &c, 1);
    if (line->cursor == strlen(line->str))
        return;
    del_char(line->str, line->cursor + 1);
    reprint_prompt(line->str);
}
