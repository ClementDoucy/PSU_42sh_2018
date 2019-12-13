/*
** EPITECH PROJECT, 2019
** buffer_copy.c
** File description:
** register the copy-buffer
*/

#include "prompt.h"
#include "tools.h"

char *buffer_copy(char *new_buffer, bool set)
{
    static char *buffer = NULL;

    if (my_strlen(new_buffer) <= 0)
        return buffer;
    if (set) {
        free(buffer);
        buffer = my_strdup(new_buffer);
    }
    return buffer;
}
