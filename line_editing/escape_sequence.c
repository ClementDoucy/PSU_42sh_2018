/*
** EPITECH PROJECT, 2019
** escape_sequence.c
** File description:
** handles the escape sequences
*/

#include "prompt.h"

static void ctrl_escape_sequence(line_t *line)
{
    char escape[3];

    read(0, &escape, 3);
    if (escape[2] == KEY_LEFT)
        key_wordgoto_head(line);
    else if (escape[2] == KEY_RIGHT)
        key_wordgoto_tail(line);
}

static void switch_sequence(line_t *line, char escape)
{
    switch (escape) {
        case KEY_FN_LEFT: key_goto_head(line);
            break;
        case KEY_LEFT: move_left(line);
            break;
        case KEY_FN_RIGHT: key_goto_tail(line);
            break;
        case KEY_RIGHT: move_right(line);
            break;
        case KEY_UP: history_up(line);
            break;
        case KEY_DOWN: history_down(line);
            break;
        case KEY_SUPPR: key_suppr(line);
            break;
        case CTRL_ESCAPE: ctrl_escape_sequence(line);
            break;
    }
}

void escape_sequence(line_t *line)
{
    char escape[2];

    read(0, &escape, 2);
    if (escape[0] == '[')
        switch_sequence(line, escape[1]);
    else if (escape[0] == '?')
        key_print_help(line);
}
