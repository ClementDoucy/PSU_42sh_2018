/*
** EPITECH PROJECT, 2019
** reprint_prompt.c
** File description:
** reprints the prompt and the content of the current command
*/

#include "prompt.h"

void reprint_prompt(char *str)
{
    termcap(CURSOR_SAVE);
    termcap(LINE_DELETE);
    print_prompt();
    my_putstr(str);
    termcap(CURSOR_RECOVER);
}
