/*
** EPITECH PROJECT, 2019
** parsing.c
** File description:
** parse command
*/

#include "mysh.h"
#include "parse.h"

void parse_command(char *cmd, char ***env, int *status)
{
    char **cmd_arr = NULL;

    if (is_simple_command(cmd)) {
        launch_process(cmd, *env, status);
        return;
    }
    if (check_redir_error(cmd)) {
        *status = 1;
        return;
    }
    if (!(cmd_arr = get_cmds(cmd))) {
        *status = 1;
        return;
    }
    manage_semi(cmd_arr, env, status);
    destroy_2d_2allocs((void **)cmd_arr);
}

bool is_simple_command(char *cmd)
{
    for (int i = 0; cmd[i]; i++)
        if (IS_AND(&(cmd[i])) || IS_OR(&(cmd[i])) ||
            PIPE(cmd[i]) || SEMI(cmd[i]) || SUP(cmd[i]) || INF(cmd[i]))
            return false;
    return true;
}

bin_str_t *gen_tree_cmd(char *cmd)
{
    char *str = NULL;
    bin_str_t *root = NULL;

    if (!(str = str_clean(cmd)))
        return NULL;
    if (str[my_strlen(str) - 1] == '\n')
        str[my_strlen(str) - 1] = '\0';
    root = build_tree(str);
    free(str);
    return root;
}

char *get_cmd(char *cmd)
{
    char *new = 0;
    size_t size = 0;
    int k = 0;

    for (int i = 0; cmd[i]; i++) {
        if (PIPE(cmd[i]) || SEMI(cmd[i]) || SUP(cmd[i]) || INF(cmd[i]))
            break;
        size++;
    }
    if (size && cmd[size - 1] == ' ')
        size--;
    if (size && cmd[0] == ' ') {
        size--;
        k = 1;
    }
    if (!(new = malloc(sizeof(char) * (size + 1))))
        return NULL;
    for (int i = 0; i < (int)size; i++, k++)
        new[i] = cmd[k];
    new[size] = '\0';
    return new;
}

char *get_operator(char *cmd)
{
    char *new = NULL;
    size_t size = 0;
    int i = 0;

    for (; cmd[i]; i++)
        if (PIPE(cmd[i]) || SEMI(cmd[i]) || SUP(cmd[i]) || INF(cmd[i]))
            break;
    if (PIPE(cmd[i]) || SEMI(cmd[i]))
        size = 1;
    if ((SUP(cmd[i]) && SUP(cmd[i + 1])) || (INF(cmd[i]) && INF(cmd[i + 1])))
        size = 2;
    else
        size = 1;
    if (!(new = malloc(sizeof(char) * (size + 1))))
        return NULL;
    for (int k = 0; k < (int)size; k++) {
        new[k] = cmd[i];
        i++;
    }
    new[size] = '\0';
    return new;
}
