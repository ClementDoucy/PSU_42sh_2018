/*
** EPITECH PROJECT, 2018
** handle_str.c
** File description:
** adds and removes char in a string
*/

#include "prompt.h"
#include "tools.h"

char *add_char(char *str, char c, size_t index)
{
    size_t len = my_strlen(str);
    char *new_str;
    size_t i = 0;

    new_str = malloc(sizeof(char) * (len + 2));
    if (new_str == NULL)
        return str;
    for (; i < index; i++)
        new_str[i] = str[i];
    new_str[i] = c;
    for (; str[i]; i++)
        new_str[i + 1] = str[i];
    new_str[i + 1] = 0;
    free(str);
    return new_str;
}

void del_char(char *str, size_t index)
{
    size_t len = my_strlen(str);

    for (; index - 1 < len; index++)
        str[index - 1] = str[index];
}
