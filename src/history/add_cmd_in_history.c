/*
** EPITECH PROJECT, 2019
** history.c
** File description:
** history
*/

#include "mysh.h"
#include "history.h"

void destroy_history_cmd(histcmd_t *cmd)
{
    free(cmd->cmd);
    free(cmd);
}

static bool is_cmd_already_exist(const history_t *history, const char *cmd)
{
    histcmd_t *tmp = history->head;

    while (tmp) {
        if (strcmp(tmp->cmd, cmd) == 0)
            return true;
        tmp = tmp->next;
    }
    return false;
}

static histcmd_t *init_new_cmd(char *cmd, int id)
{
    histcmd_t *new = malloc(sizeof(histcmd_t));

    if (!new)
        return NULL;
    new->id = id;
    new->time = time(NULL);
    new->cmd = my_strdup(cmd);
    new->next = NULL;
    new->prev = NULL;
    return new;
}

static history_t *add_new_cmd(history_t *history, char *cmd)
{
    histcmd_t *new = init_new_cmd(cmd, history->id++);
    histcmd_t *first = history->head;

    if (!new)
        return NULL;
    if (!first) {
        history->head = new;
        history->last = new;
    } else if (history->id < 100) {
        new->prev = history->last;
        history->last->next = new;
        history->last = new;
    } else {
        history->head = history->head->next;
        history->head->prev = NULL;
        destroy_history_cmd(first);
        new->prev = history->last;
        history->last->next = new;
        history->last = new;
    }
    return history;
}

history_t *add_cmd_in_history(history_t *history, char *cmd)
{
    if (is_cmd_already_exist(history, cmd) == true)
        return move_cmd_to_last(history, cmd);
    return add_new_cmd(history, cmd);
}
