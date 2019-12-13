/*
** EPITECH PROJECT, 2019
** cd.c
** File description:
** cd builtin
*/

#include "mysh.h"

void launch_cd(char *cmd, char ***env, int *status)
{
    char **argv = NULL;
    size_t size = compute_size_argv(cmd);
    char *home_path = get_env_param(*env, "HOME");
    static char *old_pwd = NULL;
    char *pwd = NULL;
    int a = 0;

    if (size < 3 && is_path_valid(cmd, size, home_path, old_pwd))
        pwd = getcwd(pwd, 64);
    if ((a = launch_cd_2(size, home_path)) == 1 || a == 84) {
        if (a == 84)
            *status = 1;
    } else {
        argv = get_argv(cmd, size);
        if (change_dir(argv, home_path, old_pwd) == 84)
            *status = 1;
    }
    get_old_pwd(&pwd, &old_pwd);
    if (home_path)
        free(home_path);
    destroy_2d_2allocs((void **)argv);
}

char *get_env_param(char **env, char *var)
{
    int i = is_var_exist(var, env);
    int k = 0;
    char *param = NULL;

    if (i == -1)
        return NULL;
    for (; env[i][k] != '\0' && env[i][k] != '='; k++);
    if (env[i][k] == '\0')
        return NULL;
    param = my_strdup(&env[i][k + 1]);
    return param;
}

int change_dir(char **argv, char *home_path, char *old_pwd)
{
    if (are_eq_str(argv[1], "~")) {
        if (!home_path || (chdir(home_path) == -1)) {
            my_putstr_stderr(home_path);
            my_puts_stderr(": No such file or directory.");
            return 84;
        }
        return 1;
    }
    if (chdir(argv[1]) != -1)
        return 1;
    else if (!are_eq_str(argv[1], "home") && !are_eq_str(argv[1], "-")) {
        my_putstr_stderr(argv[1]);
        if (access(argv[1], F_OK))
            my_puts_stderr(": No such file or directory.");
        else if (is_file_or_dir(argv[1]))
            my_puts_stderr(": Not a directory.");
        else
            my_puts_stderr(": Permission denied.");
        return 84;
    }
    return change_dir_2(argv, home_path, old_pwd);
}

int launch_cd_2(size_t size, char *home_path)
{
    if (size == 1) {
        if (!home_path || (chdir(home_path) == -1)) {
            my_puts_stderr("cd: Can't change to home directory.");
            return 84;
        }
        return 1;
    }
    if (size > 2) {
        my_puts_stderr("cd: Too many arguments.");
        return 84;
    }
    return 0;
}

int change_dir_2(char **argv, char *home_path, char *old_pwd)
{
    if (are_eq_str(argv[1], "home")) {
        if (!home_path || chdir(home_path) == -1) {
            my_putstr_stderr(argv[1]);
            my_puts_stderr(": No such file or directory.");
            return 84;
        } else {
            my_puts("~");
            return 1;
        }
    }
    if (are_eq_str(argv[1], "-")) {
        if (!old_pwd) {
            my_puts_stderr(": No such file or directory.");
            return 84;
        } else
            chdir(old_pwd);
    }
    return 1;
}
