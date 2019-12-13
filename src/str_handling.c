/*
** EPITECH PROJECT, 2019
** str_handling.c
** File description:
** string manipulation
*/

#include "mysh.h"

bool are_eq_str(char *s1, char *s2)
{
    int a = 0;
    int b = 0;
    int i = 0;
    int k = 0;

    if (!s1 || !s2)
        return false;
    for (; s1[i] != '\0' && (s1[i] == ' ' || s1[i] == '\t'); i++);
    for (; s2[k] != '\0' && (s2[k] == ' ' || s2[k] == '\t'); k++);
    for (a = i; s1[a] != '\0' && s1[a] != ' ' &&
        s1[a] != '\t' && s1[a] != '\n'; a++);
    for (b = k; s2[b] != '\0' && s2[b] != ' ' &&
        s2[b] != '\t' && s2[b] != '\n'; b++);
    if (a - i != b - k)
        return false;
    for (; s1[i] != '\0' && s2[k] != '\0'; i++) {
        if (s1[i] != s2[k])
            return false;
        k++;
    }
    return true;
}

bool are_eq_var(char *s1, char *s2)
{
    int a = 0;
    int b = 0;

    if (!s1 || !s2)
        return false;
    for (; s1[a] != '\0' && s1[a] != '='; a++);
    for (; s2[b] != '\0' && s2[b] != '='; b++);
    if (a != b)
        return false;;
    for (int i = 0; i < a; i++)
        if (s1[i] != s2[i])
            return false;
    return true;
}

int is_var_exist(char *var, char **env)
{
    for (int i = 0; env[i]; i++)
        if (are_eq_var(var, env[i]))
            return i;
    return -1;
}

bool is_empty_line(char *str)
{
    if (!str)
        return true;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] != ' ' && str[i] != '\t' &&
            str[i] != '\n' && str[i] != '\0')
            return false;
    return true;
}

void my_str_swap(char **s1, char **s2)
{
    char *save = NULL;

    save = *s1;
    *s1 = *s2;
    *s2 = save;
}
