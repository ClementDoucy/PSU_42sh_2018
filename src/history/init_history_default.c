/*
** EPITECH PROJECT, 2019
** history.c
** File description:
** history
*/

#include "mysh.h"
#include "history.h"

history_t *init_history_default(void)
{
    history_t *history = malloc(sizeof(history_t));

    if (!history)
        return NULL;
    history->head = NULL;
    history->last = NULL;
    history->id = 1;
    return history;
}
