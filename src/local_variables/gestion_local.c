/*
** EPITECH PROJECT, 2018
** window csfml
** File description:
** window csfml
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

int gestion_local(char *str)
{
    char **cut = str_to_word_array(str, " ");

    if (str == NULL)
        return 0;
    if (are_eq_str(cut[0], "set")) {
        if (cut[1] == NULL)
            gestion_var(NULL, NULL, 1, PRINT);
        else
            gestion_var(cut[1], cut[2], 1, SET);
        return 1;
    }
    if (are_eq_str(cut[0], "unset")) {
        gestion_var(cut[1], NULL, 1, UNSET);
        return 1;
    }
    return 0;
}