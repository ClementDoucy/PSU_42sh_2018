/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** destroy_2d_2allocs
*/

#include <stdlib.h>

void destroy_2d_2allocs(void **arr)
{
    if (!arr)
        return;
    if (*arr)
        free(*arr);
    free(arr);
}