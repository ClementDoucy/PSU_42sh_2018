/*
** EPITECH PROJECT, 2019
** launcher.c
** File description:
** launcher for mysh
*/

#include "mysh.h"
#include "prompt.h"

const builtin_t builtins[7] = {
    {&launch_cd, "cd"},
    {&launch_setenv, "setenv"},
    {&launch_unsetenv, "unsetenv"},
    {&launch_exit, "exit"},
    {&launch_echo, "echo"},
    {&launch_where, "where"},
    {&launch_which, "which"},
};

void launch(char **env)
{
    char *cmd = NULL;
    static int status = 0;

    while (true) {
        signal(SIGINT, catch_sigint);
        cmd = run_shell(&status);
        launch_cmd(cmd, &env, &status);
        if (cmd)
            free(cmd);
    }
}

char *run_shell(int *status)
{
    char *command = NULL;

    command = prompt();
    if (command == NULL) {
        free(command);
        command = my_strdup("exit");
    }
    else if (!is_empty_line(command))
        *status = 0;
    return command;
}

void launch_cmd(char *str, char ***env, int *status)
{
    if (is_empty_line(str))
        return;
    if (are_eq_str(str, "env") && is_simple_command(str)) {
        print_2d_str(*env);
        return;
    }
    if (gestion_history(str, env, status, SET))
        return;
    if (gestion_alias(str, status, NULL, SET))
        return;
    for (int i = 0; i < 7; i++) {
        if (is_simple_command(str) && are_eq_str(str, builtins[i].builtin)) {
            builtins[i].fn_ptr(str, env, status);
            return;
        }
        if (gestion_local(str) == 1)
            return;
    }
    parse_command(str, env, status);
}
