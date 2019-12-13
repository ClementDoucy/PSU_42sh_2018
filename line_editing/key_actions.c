/*
** EPITECH PROJECT, 2019
** key_actions.c
** File description:
** does an action corresponding to the input key
*/

#include "prompt.h"

static void control_actions(line_t *line)
{
    switch (line->key) {
        case CTRL_U: key_wholecut(line);
            break;
        case CTRL_F: key_headcut(line);
            break;
        case CTRL_K: key_tailcut(line);
            break;
        case CTRL_W: key_word_headcut(line);
            break;
        case CTRL_X: key_word_tailcut(line);
            break;
        case CTRL_Y: key_restore_buffer(line);
            break;
        case CTRL_L: clear_term(line);
            break;
        default: key_default(line);
    }
}

void key_actions(line_t *line)
{
    switch (line->key) {
        case KEY_BEG: key_goto_head(line);
            break;
        case KEY_END: key_goto_tail(line);
            break;
        case CTRL_DEL: key_word_headcut(line);
            break;
        case KEY_TAB: key_tab(line);
            break;
        case ESCAPE: escape_sequence(line);
            break;
        case KEY_DEL: key_delete(line);
            break;
        default: control_actions(line);
    }
}
