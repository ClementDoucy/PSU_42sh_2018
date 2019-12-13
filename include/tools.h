/*
** EPITECH PROJECT, 2019
** tools.h
** File description:
** header file for tools
*/

#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

static const int READ_SIZE = 20;

char *my_strdup(char *);
size_t my_strlen(char *);
char *my_strcat(char *, char *);
void my_puts(char *);
char *my_strcat(char *, char *);
void my_put_2d_str(char **);
int my_getnbr(char *);
void destroy_2d_tab(void **);
void my_putstr(char *);
void my_putstr_stderr(char *);
void print_2d_str(char **);
void my_puts_stderr(const char *);
char **realloc_2d_str(char **, size_t);
size_t str_2d_len(char **);
char **str_2d_dup(char **);
bool my_strcmp(char *, char *);
char *my_strstr(char *str, char const *to_find);
int my_char_isalpha(char const c);
int my_str_isalphanum(char const *str);
int my_char_isnum(char const c);
void **free_arr_null(void **arr, bool free_arr);
void *sfree_null(void *ptr);
int char_in(char c, char const *is_in);
char **str_to_word_array(char *strin, char *delims);
size_t my_strcountw(char *str, char *delims);

#endif
