/*
** EPITECH PROJECT, 2019
** history.c
** File description:
** history
*/

#include "mysh.h"
#include "history.h"

static history_t *move_cmd_to_last_first(history_t *history, histcmd_t *tmp)
{
    history->head = tmp->next;
    history->head->prev = NULL;
    tmp->prev = history->last;
    history->last->next = tmp;
    history->last = tmp;
    tmp->next = NULL;
    return history;
}

static history_t *move_cmd_to_last_middle(history_t *history, histcmd_t *tmp)
{
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    tmp->prev = history->last;
    tmp->next = NULL;
    history->last->next = tmp;
    history->last = tmp;
    return history;
}

history_t *move_cmd_to_last(history_t *history, char *cmd)
{
    histcmd_t *tmp = history->head;

    while (tmp) {
        if (strcmp(tmp->cmd, cmd) == 0)
            break;
        tmp = tmp->next;
    }
    tmp->time = time(NULL);
    tmp->id = history->id++;
    if (strcmp(history->head->cmd, tmp->cmd) == 0) {
        return move_cmd_to_last_first(history, tmp);
    } else if (strcmp(history->last->cmd, cmd) == 0)
        return history;
    return move_cmd_to_last_middle(history, tmp);
}
