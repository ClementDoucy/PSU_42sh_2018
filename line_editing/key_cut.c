/*
** EPITECH PROJECT, 2019
** key_cut.c
** File description:
** deletes everything around the cursor
*/

#include "prompt.h"

void key_wholecut(line_t *line)
{
    buffer_copy(line->str, true);
    line->str = calloc(1, sizeof(char));
    line->cursor = 0;
    termcap(LINE_DELETE);
    print_prompt();
}

void key_headcut(line_t *line)
{
    char *buffer = calloc(1, sizeof(char));

    while (line->cursor > 0) {
        buffer = add_char(buffer, line->str[line->cursor - 1], 0);
        del_char(line->str, line->cursor);
        line->cursor--;
        termcap(CURSOR_LEFT);
    }
    buffer_copy(buffer, true);
    reprint_prompt(line->str);
    free(buffer);
}

void key_tailcut(line_t *line)
{
    buffer_copy(&line->str[line->cursor], true);
    line->str[line->cursor] = '\0';
    reprint_prompt(line->str);
}
