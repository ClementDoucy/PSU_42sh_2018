/*
** EPITECH PROJECT, 2019
** history.h
** File description:
** header for history
*/

#ifndef HISTORY_H_
#define HISTORY_H_

#include <time.h>

typedef struct history_cmd
{
    int id;
    time_t time;
    char *cmd;
    struct history_cmd *prev;
    struct history_cmd *next;
}histcmd_t;

typedef struct history
{
    int id;
    histcmd_t *head;
    histcmd_t *last;
}history_t;

char *get_next_line(int);
char *get_history_filepath(char **env);
history_t *init_history_from_file(char ***env);
history_t *init_history_default(void);
void print_history(history_t *history, int nb);
history_t *add_cmd_in_history(history_t *history, char *cmd);
history_t *move_cmd_to_last(history_t *history, char *cmd);
void save_history(history_t *history, char **env);
char *get_history(history_t *history, char *cmd, int *status);
bool my_str_isnum(const char *str);
char *history_builtin(history_t *, char *, size_t, int *);

#endif /* HISTORY_H_ */
