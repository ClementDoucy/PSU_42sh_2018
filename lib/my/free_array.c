/*
** EPITECH PROJECT, 2018
** my_strstr
** File description:
** my_strstr
*/

#include "tools.h"

int char_in(char c, char const *is_in)
{
    for (size_t i = 0; is_in[i]; i++)
        if (c == is_in[i])
            return true;
    return false;
}

void *sfree_null(void *ptr)
{
    if (ptr)
        free(ptr);
    return NULL;
}

void **free_arr_null(void **arr, bool free_arr)
{
    if (!arr)
        return NULL;
    for (size_t i = 0; arr[i]; i++)
        free(arr[i]);
    if (free_arr == true)
        free(arr);
    return NULL;
}