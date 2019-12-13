/*
** EPITECH PROJECT, 2019
** history.c
** File description:
** history
*/

#include "mysh.h"
#include "history.h"

static int get_nb_digit_of_number(int number)
{
    int nb_digit = 0;

    while (number > 0) {
        nb_digit++;
        number /= 10;
    }
    return nb_digit;
}

static void print_id(int number)
{
    int nb_digit = get_nb_digit_of_number(number);

    for (int i = nb_digit; i < 6; i++)
        printf(" ");
    printf("%d  ", number);
}

void print_history(history_t *history, int nb)
{
    histcmd_t *tmp = history->last;
    char hour_minute[sizeof("HH:MM")] = {0};
    struct tm tm = {0};

    for (int i = 1; tmp && i < nb; i++)
        tmp = tmp->prev;
    if (!tmp)
        tmp = history->head;
    while (tmp) {
        print_id(tmp->id);
        tm = *localtime(&tmp->time);
        strftime(hour_minute, sizeof(hour_minute), "%H:%M", &tm);
        printf("%s ", hour_minute);
        printf("%s\n", tmp->cmd);
        tmp = tmp->next;
    }
}
