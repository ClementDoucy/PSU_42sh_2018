/*
** EPITECH PROJECT, 2019
** history.c
** File description:
** history
*/

#include "mysh.h"
#include "history.h"

static char *my_revstr(char *str)
{
    int i = 0;
    int max = 0;
    int end;
    char tmp;

    while (str[max])
        max++;
    end = max;
    while (i < max) {
        tmp = str[i];
        str[i] = str[max - 1];
        str[max - 1] = tmp;
        max--;
        i++;
    }
    str[end] = '\0';
    return (str);
}

static char *my_long_int_to_str(long int nb)
{
    char str[32];
    char *s = NULL;
    int i = 0;

    while (nb > 0) {
        str[i++] = nb % 10 + '0';
        nb /= 10;
    }
    str[i] = 0;
    s = strdup(str);
    s = my_revstr(s);
    return s;
}

static void write_into_history_file(int fd, histcmd_t *tmp)
{
    char *nb = NULL;

    write(fd, "#+", 2);
    nb = my_long_int_to_str(tmp->time);
    write(fd, nb, strlen(nb));
    free(nb);
    write(fd, "\n", 1);
    write(fd, tmp->cmd, strlen(tmp->cmd));
    write(fd, "\n", 1);
}

void save_history(history_t *history, char **env)
{
    char *history_path = get_history_filepath(env);
    int fd = open(history_path, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    histcmd_t *tmp = history->head;

    if (fd == -1) {
        fprintf(stderr, "Failed to open .42sh_history\n");
        return;
    }
    while (tmp) {
        write_into_history_file(fd, tmp);
        tmp = tmp->next;
    }
    free(history_path);
    close(fd);
}
