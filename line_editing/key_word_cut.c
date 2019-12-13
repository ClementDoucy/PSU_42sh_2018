/*
** EPITECH PROJECT, 2019
** key_word_cut.c
** File description:
** cuts a word
*/

#include "prompt.h"
#include "tools.h"

void key_word_headcut(line_t *line)
{
    char *buffer = calloc(1, sizeof(char));

    while (line->cursor > 0 && line->str[line->cursor - 1] == ' ') {
        buffer = add_char(buffer, line->str[line->cursor - 1], 0);
        del_char(line->str, line->cursor);
        line->cursor--;
        termcap(CURSOR_LEFT);
    }
    while (line->cursor > 0 && line->str[line->cursor - 1] != ' ') {
        buffer = add_char(buffer, line->str[line->cursor - 1], 0);
        del_char(line->str, line->cursor);
        line->cursor--;
        termcap(CURSOR_LEFT);
    }
    buffer_copy(buffer, true);
    reprint_prompt(line->str);
    free(buffer);
}

void key_word_tailcut(line_t *line)
{
    char *buffer = calloc(1, sizeof(char));

    while (line->cursor > 0 && line->str[line->cursor] == ' ') {
        buffer = add_char(buffer, line->str[line->cursor], 0);
        del_char(line->str, line->cursor + 1);
    }
    while (line->cursor > 0 && line->str[line->cursor] != ' ') {
        buffer = add_char(buffer, line->str[line->cursor], 0);
        del_char(line->str, line->cursor + 1);
    }
    buffer_copy(buffer, true);
    reprint_prompt(line->str);
    free(buffer);
}
