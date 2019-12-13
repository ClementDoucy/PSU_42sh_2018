/*
** EPITECH PROJECT, 2019
** key_tab.c
** File description:
** prints current directory content
*/

#include "prompt.h"

static char *which_dir(char *command)
{
    size_t index_of_start = strlen(command);
    size_t index_of_end = index_of_start;

    for (; index_of_start > 0; index_of_start--)
        if (command[index_of_start - 1] == ' ')
            break;
    for (; index_of_end > index_of_start; index_of_end--)
        if (command[index_of_end] == '/')
            break;
    return strndup(&command[index_of_start], index_of_end - index_of_start + 1);
}

static char *which_file(char *command)
{
    size_t index_of_start = strlen(command);
    size_t index_of_end = index_of_start;

    for (; index_of_start > 0; index_of_start--)
        if (command[index_of_start - 1] == '/')
            break;
    return strndup(&command[index_of_start], index_of_end - index_of_start + 1);
}

static void prepare_auto_complete(line_t *line)
{
    char *directory = which_dir(line->str);
    char *file = which_file(line->str);

    auto_complete(line, directory, file);
    free(directory);
    free(file);
}

void key_tab(line_t *line)
{
    size_t len = strlen(line->str);

    if (line->cursor != len)
        return;
    if (len > 0)
        prepare_auto_complete(line);
}
