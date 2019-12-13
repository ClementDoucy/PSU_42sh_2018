/*
** EPITECH PROJECT, 2019
** auto_complete.c
** File description:
** handle auto completion
*/

#include "prompt.h"
#include <sys/stat.h>

static void auto_complete_command(line_t *line, char *directory,
    char *file, char *to_complete)
{
    struct stat sb;

    for (int i = strlen(file); to_complete[i]; i++) {
        line->str = add_char(line->str, to_complete[i], line->cursor);
        line->cursor++;
        reprint_prompt(line->str);
        termcap(CURSOR_RIGHT);
    }
    file = my_strcat(directory, to_complete);
    if (stat(file, &sb) != -1) {
        line->str = add_char(line->str,
            (S_ISDIR(sb.st_mode)) ? ('/') : (' '), line->cursor);
        line->cursor++;
        reprint_prompt(line->str);
        termcap(CURSOR_RIGHT);
    }
    free(file);
}

static void print_files(char *directory, char **file_tab)
{
    char *full_file = NULL;
    struct stat sb;

    printf("\n");
    for (int i = 0; file_tab && file_tab[i]; i++) {
        full_file = my_strcat(directory, file_tab[i]);
        if (stat(full_file, &sb) == -1)
            break;
        if (sb.st_mode & __S_IFDIR)
            printf("\e[38;5;33m%s\e[0m\t", file_tab[i]);
        else if (sb.st_mode & __S_IEXEC)
            printf("\e[38;5;40m%s\e[0m\t", file_tab[i]);
        free(full_file);
    }
    printf("\n");
}

void auto_complete(line_t *line, char *directory, char *file)
{
    size_t file_count = 0;
    char **file_tab = get_files(directory, file, &file_count);

    if (file_tab == NULL || file_count == 0)
        return;
    if (file_count == 1)
        auto_complete_command(line, directory, file, file_tab[0]);
    else {
        print_files(directory, file_tab);
        print_prompt();
        my_putstr(line->str);
    }
}
