/*
** EPITECH PROJECT, 2019
** history.c
** File description:
** history
*/

#include "mysh.h"
#include "history.h"

static int get_history_nb(history_t *history)
{
    int nb = 0;
    histcmd_t *tmp = history->head;

    while (tmp) {
        nb++;
        tmp = tmp->next;
    }
    return nb;
}

char *history_arrows(history_t *history, int *count, cmd_t type)
{
    histcmd_t *tmp = history->last;

    if (type == UP && *count < get_history_nb(history))
        *count += 1;
    else if (type == DOWN && *count > 0)
        *count -= 1;
    for (int i = 0; i < *count && tmp; i++)
        tmp = tmp->prev;
    if (tmp)
        return tmp->cmd;
    return NULL;
}

char *gestion_history(char *cmd, char ***env, int *status, cmd_t type)
{
    static history_t *history = NULL;
    static int count = -1;
    size_t size = compute_size_argv(cmd);

    if (!history)
        if (!(history = init_history_from_file(env)))
            history = init_history_default();
    if (type == GET)
        return get_history(history, cmd, status);
    if (type == UP || type == DOWN)
        return history_arrows(history, &count, type);
    count = -1;
    history = add_cmd_in_history(history, cmd);
    if (strcmp(cmd, "exit") == 0) {
        save_history(history, *env);
        return NULL;
    }
    if (strncmp(cmd, "history", 7) == 0 && (cmd[7] == ' ' || cmd[7] == 0))
        return history_builtin(history, cmd, size, status);
    return NULL;
}
