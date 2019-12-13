/*
** EPITECH PROJECT, 2019
** where.c
** File description:
** find all the occurences of a command
*/

#include "mysh.h"

static const char *default_path = "/usr/bin:/bin";

static const char *builtins[] = {"cd", "setenv", "unsetenv", "exit",
                                "echo", "where", "which", NULL};

static void seek_command(char **env, char *arg)
{
    int i = 0;
    char **bin_path;
    char *dir;
    char *path;

    if ((i = is_var_exist("PATH", env)) == -1)
        bin_path = str_split(default_path, ':');
    else
        bin_path = str_split(env[i], ':');
    for (int i = 0; bin_path[i]; i++) {
        dir = my_strcat(bin_path[i], "/");
        path = my_strcat(dir, arg);
        if (!access(path, X_OK))
            printf("%s\n", path);
        free(dir);
        free(path);
    }
}

static void where_command(char *arg, char **env)
{
    if (is_filepath(arg)) {
        printf("where: / in command makes no sense\n");
        return;
    }
    for (int i = 0; builtins[i]; i++)
        if (strcmp(builtins[i], arg) == 0)
            printf("%s is a shell built-in\n", arg);
    seek_command(env, arg);
}

void launch_where(char *cmd, char ***env, int *status)
{
    char **argv = launch_argv(cmd);

    if (argv[1] == NULL) {
        *status = 1;
        printf("where: Too few arguments.\n");
        return;
    }
    for (int i = 1; argv && argv[i]; i++) {
        where_command(argv[i], *env);
    }
    destroy_2d_2allocs((void **)argv);
    *status = 0;
}
