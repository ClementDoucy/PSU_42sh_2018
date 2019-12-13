/*
** EPITECH PROJECT, 2019
** alias.h
** File description:
** header for alias
*/

#ifndef ALIAS_H_
#define ALIAS_H_

enum alias
{
    KEY,
    VALUE
};

void print_alias_tab(char ***alias);
void print_alias_simple(char ***alias, const char *key);
char ***add_alias(char ***alias, char *key, char *value);
char ***init_alias_tab_default(void);
char *get_alias_from_argv(char *cmd, int state);
char *get_alias_from_argv_more_3_arguments(char *cmd, size_t size);
void destroy_alias(char ***alias);
char ***sort_alias(char ***tab);
bool is_alias(char ***alias, const char *name);
char *get_alias(char ***alias, const char *name);
size_t get_alias_nb(char ***alias);
char ***unalias_builtin(char ***alias, char *cmd, size_t size, int *status);
char ***alias_builtin(char ***alias, char *cmd, size_t size, int *status);

#endif /* ALIAS_H_ */
