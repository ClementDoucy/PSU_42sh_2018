/*
** EPITECH PROJECT, 2019
** key_word_goto.c
** File description:
** goesto a surrounding word
*/

#include "prompt.h"

void key_wordgoto_head(line_t *line)
{
    while (line->cursor > 0 && line->str[line->cursor - 1] == ' ') {
        line->cursor--;
        termcap(CURSOR_LEFT);
    }
    while (line->cursor > 0 && line->str[line->cursor - 1] != ' ') {
        line->cursor--;
        termcap(CURSOR_LEFT);
    }
}

void key_wordgoto_tail(line_t *line)
{
    size_t len = strlen(line->str);

    while (line->cursor < len && line->str[line->cursor] != ' ') {
        line->cursor++;
        termcap(CURSOR_RIGHT);
    }
    while (line->cursor < len && line->str[line->cursor] == ' ') {
        line->cursor++;
        termcap(CURSOR_RIGHT);
    }
}
