/*
** EPITECH PROJECT, 2019
** setenv.c
** File description:
** set environnement
*/

#include "mysh.h"

void launch_setenv(char *cmd, char ***env, int *status)
{
    size_t size = compute_size_argv(cmd);

    if (size > 3) {
        my_puts_stderr("setenv: Too many arguments.");
        *status = 1;
        return;
    }
    if (size == 1) {
        print_2d_str(*env);
        return;
    }
    if (size == 2) {
        *env = add_var(cmd, *env, status);
        return;
    }
    if (size == 3) {
        *env = add_var_and_param(cmd, *env, status);
        return;
    }
}

char **add_var(char *cmd, char **env, int *status)
{
    char **argv = get_argv(cmd, 2);
    char *var = my_strcat(argv[1], "=");
    size_t size = str_2d_len(env);

    if (!is_valid_var(argv[1], status)) {
        free(var);
        destroy_2d_2allocs((void **)argv);
        return env;
    }
    if (is_var_exist(var, env) == -1) {
        env = realloc_2d_str(env, 1);
        env[(int)size - 1] = my_strdup(var);
        env[(int)size] = NULL;
    }
    free(var);
    destroy_2d_2allocs((void **)argv);
    return env;
}

char **add_var_and_param(char *cmd, char **env, int *status)
{
    char **argv = get_argv(cmd, 3);
    char *var = my_strcat(argv[1], "=");
    size_t size = str_2d_len(env);
    int a = is_var_exist(var, env);

    if (!is_valid_var(argv[1], status))
        return env;
    if (is_var_exist(var,env) != -1) {
        for (int i = 0; env[a][i] != '\0'; i++)
            if (env[a][i] == '=')
                env[a][i + 1] = '\0';
        env[a] = my_strcat(env[a], argv[2]);
    } else {
        env = realloc_2d_str(env, 1);
        env[(int)size - 1] = my_strcat(var, argv[2]);
        env[(int)size] = NULL;
    }
    free(var);
    destroy_2d_2allocs((void **)argv);
    return env;
}

bool is_valid_var(char *var, int *status)
{
    if ((var[0] < 65 || var[0] > 90) && (var[0] < 97 || var[0] > 122)) {
        *status = 1;
        my_puts_stderr("setenv: Variable name must begin with a letter.");
        return false;
    }
    for (int i = 1; var[i] != '\0'; i++)
        if ((var[i] < 48 || var[i] > 57) && (var[i] < 65 || var[i] > 90) &&
            (var[i] < 97 || var[i] > 122)) {
            my_putstr_stderr("setenv: Variable name must contain ");
            my_puts_stderr("alphanumeric characters.");
            *status = 1;
            return false;
        }
    return true;
}
