/*
** EPITECH PROJECT, 2019
** key_arrows.c
** File description:
** handles the the key movements
*/

#include "prompt.h"
#include "mysh.h"

void history_up(line_t *line)
{
    char *history = gestion_history(NULL, NULL, 0, UP);

    if (!history)
        return;
    free(line->str);
    line->str = strdup(history);
    line->cursor = strlen(line->str);
    termcap(LINE_DELETE);
    print_prompt();
    my_putstr(line->str);
}

void history_down(line_t *line)
{
    char *history = gestion_history(NULL, NULL, 0, DOWN);

    if (!history)
        return;
    free(line->str);
    line->str = strdup(history);
    line->cursor = strlen(line->str);
    termcap(LINE_DELETE);
    print_prompt();
    my_putstr(line->str);
}

void move_left(line_t *line)
{
    if (line->cursor <= 0)
        return;
    line->cursor--;
    termcap(CURSOR_LEFT);
}

void move_right(line_t *line)
{
    if (line->cursor >= strlen(line->str))
        return;
    line->cursor++;
    termcap(CURSOR_RIGHT);
}
