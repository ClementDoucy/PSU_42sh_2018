/*
** EPITECH PROJECT, 2018
** my_strstr
** File description:
** my_strstr
*/

#include "tools.h"

int my_char_isalpha(char const c)
{
    int a = 0;

    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        a = 1;
    else
        a = 0;
    return (a);
}

int my_char_isnum(char const c)
{
    int a = 0;

    if ((c >= 48) && (c <= 57))
        a = 1;
    else
        a = 0;
    return (a);
}

int my_str_isalphanum(char const *str)
{
    int a = 0;

    for (int i = 0; str[i]; i++) {
        if (my_char_isnum(str[i]) == 1 || my_char_isalpha(str[i]) == 1)
            a = 1;
        else
            return (0);
    }
    return (a);
}

char *my_strstr(char *str, char const *to_find)
{
    int a = 0;
    int d = 0;
    char *tempo;
    int tmp;

    while (str[a] != '\0') {
        if (str[a] == to_find[d]) {
            d++;
            if (to_find[d] == '\0' && my_char_isalpha(str[a + 1]) == 0) {
                tmp = (a-d)+1;
                return (tempo = &str[tmp]);
            }
        }
        else {
            return (NULL);
        }
        a++;
    }
    return (NULL);
}
