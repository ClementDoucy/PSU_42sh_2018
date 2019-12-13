/*
** EPITECH PROJECT, 2019
** unsetenv.c
** File description:
** unset environnement
*/

#include "mysh.h"

void launch_unsetenv(char *cmd, char ***env, int *status)
{
    size_t size = compute_size_argv(cmd);
    char **argv = NULL;
    char *tmp = NULL;

    if (size == 1) {
        my_puts_stderr("unsetenv: Too few arguments.");
        *status = 1;
        return;
    }
    argv = get_argv(cmd, size);
    for (int i = 1; argv[i]; i++) {
        tmp = argv[i];
        argv[i] = my_strcat(argv[i], "=");
        free(tmp);
    }
    for (int i = 1; argv[i]; i++)
        if (is_var_exist(argv[i], *env) != -1)
            *env = reduct_env(argv[i], *env);
    destroy_2d_2allocs((void **)argv);
}

char **reduct_env(char *var, char **env)
{
    char *tmp = NULL;
    int i = 0;

    for (; !are_eq_var(var, env[i]); i++);
    for (; env[i + 1]; i++) {
        tmp = env[i];
        env[i] = env[i + 1];
        env[i + 1] = tmp;
    }
    free(env[i]);
    env[i] = NULL;
    return env;
}

bool is_file_or_dir(char *fp)
{
    struct stat *sb = malloc(sizeof(struct stat));

    if (!sb)
        return true;
    stat(fp, sb);
    if (S_ISDIR(sb->st_mode)) {
        free(sb);
        return false;
    }
    free(sb);
    return true;
}
