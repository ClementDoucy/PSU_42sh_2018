/*
** EPITECH PROJECT, 2019
** history.c
** File description:
** history
*/

#include "mysh.h"
#include "history.h"
#include <ctype.h>

bool my_str_isnum(const char *str)
{
    for (int i = 0; str[i]; i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}

static char *history_more_args(history_t *history, char *cmd, \
        int *status, size_t size)
{
    char **args = str_to_word_array(cmd, " ");

    if (!args)
        return NULL;
    if (size > 3) {
        printf("history: Too many arguments.\n");
        *status = 1;
        return ("OK");
    }
    if (my_str_isnum(args[1]) == true) {
        print_history(history, atoi(args[1]));
        *status = 0;
    } else if (args[1][0] == '-' && my_str_isnum(&args[1][1]) == true){
        printf("Usage: history [-chrSLMT] [# number of events].\n");
        *status = 1;
    } else {
        printf("history: Badly formed number.\n");
        *status = 1;
    }
    destroy_2d_tab((void **)args);
    return ("OK");
}

char *history_builtin(history_t *history, char *cmd, size_t size, int *status)
{
    if (size == 1) {
        print_history(history, 100);
        *status = 0;
        return ("OK");
    } else if (size >= 2)
        return history_more_args(history, cmd, status, size);
    return NULL;
}
