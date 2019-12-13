/*
** EPITECH PROJECT, 2019
** command.c
** File description:
** manage command part
*/

#include "mysh.h"

void launch_exit(char *cmd, char ***env, int *status)
{
    int a = 0;
    size_t size = compute_size_argv(cmd);
    char **argv = get_argv(cmd, size);

    if (size > 2 || !is_number(argv[1])) {
        my_puts_stderr("exit: Expression Syntax.");
        destroy_2d_2allocs((void **)argv);
        return;
    }
    a = my_getnbr(cmd);
    if (*status != 0)
        a = *status;
    if (isatty(0))
        my_puts("exit");
    free(cmd);
    destroy_2d_2allocs((void **)argv);
    destroy_2d_tab((void **)*env);
    exit(a);
}

bool is_number(char *str)
{
    int i = 0;

    if (!str)
        return true;
    if (str[0] == '-')
        i++;
    for (; str[i] != '\0'; i++)
        if (str[i] < 48 || str[i] > 57)
            return false;
    return true;
}

bool check_crash(int *status)
{
    int sig = 0;

    if (!WIFSIGNALED(*status))
        return false;
    sig = WTERMSIG(*status);
    if (sig != 8)
        my_putstr_stderr(strsignal(sig));
    else
        my_putstr_stderr("Floating exception");
    if (WCOREDUMP(*status))
        my_putstr_stderr(" (core dumped)");
    write(2, "\n", 1);
    return true;
}

void check_child_error(char *str)
{
    if (is_filepath(str) && !access(str, F_OK)) {
        if (!access(str, X_OK) && is_file_or_dir(str)) {
            my_print(2, "%s: Exec format error. Wrong Architecture.\n", str);
            return;
        } else {
            my_print(2, "%s: Permission denied.\n", str);
            return;
        }
    } else {
        my_print(2, "%s: Command not found.\n", str);
        return;
    }
}

bool is_filepath(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '/')
            return true;
    return false;
}
