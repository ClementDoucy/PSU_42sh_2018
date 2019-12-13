/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** replace
*/

#ifndef REPLACE_H_
    #define REPLACE_H_

#include <stdbool.h>

#define skip_esc(word)  if (*word == '\\') {\
                            *word = '\0';   \
                            word++;         \
                            continue;       \
                        }                   \

bool expand_backslash(char *str);
char *expand_on_backslach(char *cmd);
char *replace_vars(char *word, int *status);
char *replace_alias(char *word, int *status);
char ***replace_special_words(char ***wcmds);
void replace_globbings(char ***cmd, char *word, int *status, size_t *i);
char *remove_inhibitors(char *word, int *status);
char *replace_magic_quotes(char *word, int *status);

#endif /* !REPLACE_H_ */
