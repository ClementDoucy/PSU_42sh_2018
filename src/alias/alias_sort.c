/*
** EPITECH PROJECT, 2019
** alias_sort.c
** File description:
** sorts the alias array by ascii order
*/

#include "mysh.h"
#include "alias.h"

static int ascii_sort(void const *a, void const *b)
{
    const char *const *pa = *(const char ***)a;
    const char *const *pb = *(const char ***)b;

    return strcmp(*pa, *pb);
}

char ***sort_alias(char ***tab)
{
    int nb = 0;

    while (tab[nb])
        nb++;
    qsort(tab, nb, sizeof(*tab), ascii_sort);
    return tab;
}
