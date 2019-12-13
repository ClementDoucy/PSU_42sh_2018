/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** parse
*/

#ifndef PARSE_H_
    #define PARSE_H_

#include <stdio.h>
#include <stdbool.h>
#include "myerror.h"

enum {
    SINGLE_QUOTE    = '\'',
    DOUBLE_QUOTE    =  '"',
    MAGIC_QUOTE     =  '`',
    CMD_SEP         =  ';',
    L_PAR           =  '(',
    R_PAR           =  ')',
    ESC             = '\\',
};

char ***parse_cmd(const char *cmd);
char ***replace_special_words(char ***wcmds);

void delete_cmds(char **cmds);
void delete_wcmds(char ***wcmds);
void delete_word_cmd(char **wcmd);

char *skip_spaces(char *str);
char *skip_any(char *str, size_t *endw);
char *skip_quotes(char *str, size_t *endw, int *status);

size_t arrlen(char **arr);
char *dup_word(char *start, char *end);

char ***get_wcmds(char **cmds);
char **get_cmds(const char *cmd);
const char *which_op(char *start);
char *preprocess_wcmd(char *cmd, size_t *endw);
char *get_word(char *cmd, size_t *endw, int *status);
char **get_word_cmd(char *cmd);

bool is_op(char *start);
size_t sepcmds(char *cmd, int *status);

#endif /* !PARSE_H_ */
