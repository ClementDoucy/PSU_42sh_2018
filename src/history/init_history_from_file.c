/*
** EPITECH PROJECT, 2019
** history.c
** File description:
** history
*/

#include "mysh.h"
#include "history.h"

histcmd_t *create_new_histcmd(int id, char *str, FILE *stream)
{
    histcmd_t *hist = malloc(sizeof(histcmd_t));
    size_t len = 0;
    ssize_t nread = 0;

    if (!hist)
        return NULL;
    hist->id = id++;
    if (strncmp(str, "#+", 2)) {
        return NULL;
    }
    hist->time = atol(&str[2]);
    if ((nread = getline(&str, &len, stream)) == -1)
        return NULL;
    str[nread - 1] = 0;
    hist->cmd = str;
    hist->prev = NULL;
    hist->next = NULL;
    return hist;
}

static int add_history_one_command(history_t *history, char *str, FILE *stream)
{
    histcmd_t *hist = create_new_histcmd(history->id++, str, stream);
    histcmd_t *tmp = NULL;

    if (!hist)
        return 84;
    if (!history->head) {
        history->head = hist;
        history->last = hist;
    } else {
        tmp = history->head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = hist;
        history->last = hist;
        hist->prev = tmp;
    }
    return 0;
}

char *get_history_filepath(char **env)
{
    char *path = NULL;

    if (!env)
        return NULL;
    for (int i = 0; env[i]; i++)
        if (!strncmp(env[i], "HOME", 4) && env[i][5] != 0)
            path = my_strdup(&env[i][5]);
    if (!path)
        return NULL;
    path = my_strcat(path, "/.42sh_history");
    return path;
}

history_t *init_history_from_file(char ***env)
{
    history_t *history = malloc(sizeof(history_t));
    char *history_path = NULL;
    FILE *stream = 0;
    size_t len = 0;
    char *str = NULL;

    if (!env || !history)
        return NULL;
    history_path = get_history_filepath(*env);
    history->id = 1;
    history->head = NULL;
    history->last = NULL;
    if ((stream = fopen(history_path, "r")) == NULL)
        return history;
    while (getline(&str, &len, stream) != -1)
        add_history_one_command(history, str, stream);
    free(history_path);
    fclose(stream);
    return history;
}
