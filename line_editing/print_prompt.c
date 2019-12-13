/*
** EPITECH PROJECT, 2019
** print_prompt.c
** File description:
** prints the prompt
*/

#include "prompt.h"
#include "mysh.h"

static const char *BOL = "\e[1m";
static const char *BLU = "\e[34m";
static const char *YEL = "\e[33m";
static const char *RED = "\e[31m";
static const char *GRN = "\e[32m";
static const char *RES = "\e[0m";

static int get_index_slash(char *path)
{
    for (int i = my_strlen(path) - 1; path && i >= 0; i--)
        if (path[i] == '/')
            return i;
    return -1;
}

static void print_path(char *path)
{
    int index = get_index_slash(path);

    if (index <= 0)
        printf(path);
    else
        printf(&path[++index]);
}

static void print_git_branch(void)
{
    int fd = open("./.git/HEAD", O_RDONLY);
    char *git_str = NULL;
    size_t index;

    if ((git_str = get_next_line(fd)) != NULL) {
        for (index = strlen(git_str); index > 0; index--)
            if (git_str[index] == '/')
                break;
        printf("%s%sgit:(%s%s%s) %s", BOL, BLU, RED,
            &git_str[++index], BLU, RES);
        close(fd);
        free(git_str);
    }
}

void print_prompt(void)
{
    char path[PATH_MAX];

    printf("%s%s➜  %s", BOL, GRN, YEL);
    if (getcwd(path, sizeof(path)))
        print_path(path);
    printf("%s ", RES);
    print_git_branch();
    fflush(stdout);
}
