/*
** EPITECH PROJECT, 2019
** string_parsing.c
** File description:
** functions to parse string
*/

#include "mysh.h"

char **str_split(const char *str, char c)
{
    int i = 0;
    int k = 0;
    size_t size = 0;
    char **arr = NULL;

    if (!str || !(size = split_len(str, c)) ||
        !(arr = malloc(sizeof(char *) * (size + 1))))
        return NULL;
    for (; str[i] == c; i++);
    for (; str[i]; i++)
        if (!i || (str[i] && str[i] != c && str[i - 1] == c)) {
            arr[k] = dup_until_delim(&str[i], c);
            k++;
        }
    arr[k] = NULL;
    return arr;
}

size_t split_len(const char *str, char c)
{
    size_t size = 0;
    int i = 0;

    for (; str[i] == c; i++);
    if (!str[i])
        return 0;
    size = 1;
    for (; str[i]; i++)
        if (str[i + 1] && str[i] == c && str[i + 1] != c)
            size++;
    return size;
}

char *dup_until_delim(const char *str, char c)
{
    size_t size = 0;
    char *new = NULL;

    for (; str[size] && str[size] != c; size++);
    if (!(new = malloc(sizeof(char) * (size + 1))))
        return NULL;
    for (int i = 0; i < (int)size; i++)
        new[i] = str[i];
    new[size] = '\0';
    return new;
}

char *str_clean(char *str)
{
    char *new = NULL;
    int i = 0;
    int k = 0;

    if (!str || !(new = malloc(sizeof(char) * (my_strlen(str) + 1))))
        return NULL;
    for (; str[i] == ' ' || str[i] == '\t'; i++);
    for (; str[i]; i++) {
        if (str[i] != ' ' && str[i] != '\t') {
            new[k] = str[i];
            k++;
        }
        if (str[i + 1] && !is_empty_line(&str[i]) &&
            (str[i] == ' ' || str[i] == '\t')
            && str[i + 1] != ' ' && str[i + 1] != '\t') {
            new[k] = ' ';
            k++;
        }
    }
    new[k] = '\0';
    return new;
}

char **cmd_split(char *cmd)
{
    char **argv = NULL;
    char *tmp = NULL;

    if (!cmd)
        return NULL;
    if (!(tmp = str_clean(cmd)))
        return NULL;
    if (!(argv = str_split(tmp, ';')))
        return NULL;
    free(tmp);
    return argv;
}
