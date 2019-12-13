/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** arrlen
*/

#include <stdlib.h>

size_t arrlen(char **arr)
{
    size_t len = 0;

    for (; arr[len] != NULL; len++);
    return len;
}