/*
** EPITECH PROJECT, 2019
** path_handling.c
** File description:
** path handling
*/

#include "mysh.h"

static const char *default_path = "/usr/bin:/bin";

char *launch_bin(char *cmd, char **env)
{
    char **bin_path = NULL;
    char *binary = NULL;
    int i = 0;

    if ((i = is_var_exist("PATH", env)) == -1)
        bin_path = str_split(default_path, ':');
    else
        bin_path = get_path(env, i);
    binary = launch_research(cmd, bin_path);
    destroy_2d_tab((void **)bin_path);
    return binary;
}

char **get_path(char **env, int i)
{
    char **bin_path = NULL;
    int k = 0;
    int l = 1;
    size_t size = 0;

    for (; env[i][k] != '\0' && env[i][k] != '/'; k++);
    if (env[i][k] == '\0')
        return NULL;
    size = compute_size_path(&env[i][k]);
    if (!(bin_path = malloc(sizeof(char *) * (size + 1))))
        return NULL;
    bin_path[0] = path_dup(&env[i][k]);
    for (; env[i][k] != '\0' && env[i][k] != ':'; k++);
    for (; env[i][k] != '\0'; k++)
        if (env[i][k] == ':' && env[i][k + 1] != '\0'
            && env[i][k + 1] != ':') {
            bin_path[l] = path_dup(&env[i][k]);
            l++;
        }
    bin_path[l] = NULL;
    return bin_path;
}

size_t compute_size_path(char *path)
{
    size_t size = 1;

    for (int i = 0; path[i]; i++)
        if (path[i] == ':' && (path[i + 1] != ':' || path[i + 1] != '\0'))
            size++;
    return size;
}

char *path_dup(char *path)
{
    size_t size = 0;
    char *str = NULL;
    int i = 0;

    for (; path[i] != '\0' && path[i] == ':'; i++);
    for (int k = i; path[k] != '\0' && path[k] != ':'; k++)
        size++;
    if (!(str = malloc(sizeof(char) * (size + 1))))
        return NULL;
    for (int k = 0; path[i] != '\0' && path[i] != ':'; k++) {
        str[k] = path[i];
        i++;
    }
    str[size] = '\0';
    return str;
}

bool is_path_valid(char *cmd, size_t size, char *home_path, char *old_pwd)
{
    char **argv = NULL;

    if (size == 1)
        if (!home_path || access(home_path, R_OK | W_OK | X_OK))
            return false;
    argv = get_argv(cmd, size);
    if (are_eq_str(argv[1], "~"))
        if (!home_path || access(home_path, R_OK | W_OK | X_OK)) {
            destroy_2d_2allocs((void **)argv);
            return false;
        }
    if (argv[1] && !are_eq_str(argv[1], "home") && !are_eq_str(argv[1], "-"))
        if (access(argv[1], R_OK)) {
            destroy_2d_2allocs((void **)argv);
            return false;
        }
    if (!is_path_valid_2(argv, home_path, old_pwd))
        return false;
    destroy_2d_2allocs((void **)argv);
    return true;
}
