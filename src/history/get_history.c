/*
** EPITECH PROJECT, 2019
** history.c
** File description:
** history
*/

#include "mysh.h"
#include "history.h"

static char *get_history_from_pos_nb(history_t *history, char *arg, int *status)
{
    histcmd_t *tmp = history->head;

    while (tmp) {
        if (tmp->id == atoi(arg))
            return tmp->cmd;
        tmp = tmp->next;
    }
    printf("%s: Event not found.\n", arg);
    *status = 1;
    return NULL;
}

static char *get_history_from_neg_nb(history_t *history, char *arg, int *status)
{
    histcmd_t *tmp = history->head;
    int index = history->id + atoi(arg);

    while (tmp) {
        if (tmp->id == index)
            return tmp->cmd;
        tmp = tmp->next;
    }
    printf("%d: Event not found.\n", index);
    *status = 1;
    return NULL;
}

static char *get_history_from_string(history_t *history, char *arg, int *status)
{
    histcmd_t *tmp = history->last;
    while (tmp) {
        if (strncmp(tmp->cmd, arg, strlen(arg)) == 0)
            return tmp->cmd;
        tmp = tmp->prev;
    }
    printf("%s: Event not found.\n", arg);
    *status = 1;
    return NULL;
}

char *get_history(history_t *history, char *cmd, int *status)
{
    char *arg = NULL;

    if (strcmp(cmd, "!") == 0)
        return cmd;
    arg = &cmd[1];
    *status = 0;
    if (my_str_isnum(arg) == true)
        return get_history_from_pos_nb(history, arg, status);
    else if (arg[0] == '-' && my_str_isnum(&arg[1]) == true)
        return get_history_from_neg_nb(history, arg, status);
    else
        return get_history_from_string(history, arg, status);
    *status = 1;
    return NULL;
}
