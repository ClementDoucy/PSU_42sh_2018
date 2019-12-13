/*
** EPITECH PROJECT, 2019
** process.c
** File description:
** launch processus
*/

#include "mysh.h"
#include "parse.h"
#include "replace.h"

void launch_process(char *cmd, char **env, int *status)
{
    pid_t pid = fork();

    if (pid == -1)
        return;
    if (!pid)
        manage_child(cmd, env);
    if (pid > 0) {
        wait(status);
        if (!(check_crash(status)))
            *status = WEXITSTATUS(*status);
    }
}

char **launch_argv(char *cmd)
{
    int status = 0;
    char **argv = NULL;

    argv = get_word_cmd(cmd);
    if (!argv)
        return NULL;
    *argv = replace_alias(*argv, &status);
    for (size_t i = 0; status == 0 && argv[i] != NULL; (argv[i]) ? i++ : 0) {
        argv[i] = remove_inhibitors(argv[i], &status);
        if (status == 0)
            replace_globbings(&argv, argv[i], &status, &i);
    }
    if (status != 0)
        return NULL;
    return argv;
}

size_t compute_size_argv(char *cmd)
{
    size_t size = 0;
    int i = 0;

    if (!cmd)
        return 0;
    if (cmd[my_strlen(cmd) - 1] == '\n')
        cmd[my_strlen(cmd) - 1] = '\0';
    for (; cmd[i] == ' ' || cmd[i] == '\t'; i++);
    for (; cmd[i] != '\0'; i++)
        if ((cmd[i] == ' ' || cmd[i] == '\t') &&
            (cmd[i + 1] != '\0' && cmd[i + 1] != '\t' && cmd[i + 1] != ' '))
            size++;
    return size + 1;
}

char *arg_dup(char *src)
{
    size_t size = 0;
    char *str = NULL;

    if (!src)
        return NULL;
    for (int k = 0; src[k] != '\0' && src[k] != ' ' && src[k] != '\t'; k++)
        size++;
    str = malloc(sizeof(char) * (size + 1));
    if (!str)
        return NULL;
    for (int i = 0; src[i] != '\0' && src[i] != ' ' && src[i] != '\t'; i++)
        str[i] = src[i];
    str[size] = '\0';
    return str;
}

char **get_argv(char *cmd, size_t size)
{
    int i = 0;
    int k = 1;
    char **argv = malloc(sizeof(char *) * (size + 1));

    if (!argv)
        return NULL;
    for (; cmd[i] == ' ' || cmd[i] == '\t'; i++);
    argv[0] = arg_dup(&cmd[i]);
    for (; cmd[i] != '\0'; i++)
        if ((cmd[i] == ' ' || cmd[i] == '\t') &&
            (cmd[i + 1] != '\0' && cmd[i + 1] != '\t' && cmd[i + 1] != ' ')) {
            i++;
            argv[k] = arg_dup(&cmd[i]);
            k++;
        }
    argv[k] = NULL;
    return argv;
}
