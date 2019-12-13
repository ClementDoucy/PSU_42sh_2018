/*
** EPITECH PROJECT, 2019
** key_help.c
** File description:
** prints a help message
*/

#include "prompt.h"
#include "tools.h"

static const char *help_str[] = {
    "Welcome to 42zsh's line-editing tool.",
    "Multiple inputs are available for you to use.",
    "- left and right arrow keys to move the cursor.",
    "- suppr for forward delete.",
    "- backspace for backward delete.",
    "- up and down arrow keys for navigating in the history.",
    "- tabulations for autocompletion.",
    "    One result will autocomplete.",
    "    Multiple results will be shown.",
    "- ^backspace to delete a whole word.",
    "- Fn + left_arrow to go the left of the line.",
    "- Fn + right_arrow to go the right of the line.",
    "- ^A to go the left of the line.",
    "- ^E to go the right of the line.",
    "- ^left_arrow to go the word at the left.",
    "- ^right_arrow to go the word at the right.",
    "- ^U to cut the whole line.",
    "- ^K to cut the line to the right.",
    "- ^F to cut the line to the left.",
    "- ^W to cut the word at the left.",
    "- ^X to cut the word at the right.",
    "- ^L to clear the screen.",
    "- alt-? to print this help message.",
    "Printable characters are added to the line",
    "Unknown sequences are skipped.",
    NULL};

void key_print_help(line_t *line)
{
    printf("\n\n");
    for (size_t i = 0; help_str[i] != NULL; i++)
        printf("%s\n", help_str[i]);
    printf("\n");
    print_prompt();
    my_putstr(line->str);
    for (size_t i = 0; i < my_strlen(line->str) - line->cursor; i++)
        termcap(CURSOR_LEFT);
}
