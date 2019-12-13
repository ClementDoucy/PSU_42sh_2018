/*
** EPITECH PROJECT, 2019
** prompt.h
** File description:
** header for prompt
*/

#ifndef PROMPT_H_
#define PROMPT_H_

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <term.h>
#include <fcntl.h>
#include <sys/stat.h>

#undef KEY_UP
#undef KEY_LEFT
#undef KEY_DOWN
#undef KEY_RIGHT

enum {
    CTRL_D       =    4,
    CTRL_F       =    6,
    CTRL_K       = '\v',
    CTRL_L       = '\f',
    CTRL_U       =   21,
    CTRL_W       =   23,
    CTRL_X       =   24,
    CTRL_Y       =   25,
    CTRL_DEL     = '\b',
    NEWLINE      = '\n',
    ESCAPE       =   27,
    CTRL_ESCAPE  =   49,
    KEY_BEG      =    1,
    KEY_END      =    5,
    KEY_TAB      = '\t',
    KEY_SUPPR    =   51,
    KEY_UP       =   65,
    KEY_DOWN     =   66,
    KEY_RIGHT    =   67,
    KEY_FN_RIGHT =   70,
    KEY_LEFT     =   68,
    KEY_FN_LEFT  =   72,
    KEY_DEL      =  127,
};

#define termcap(id) my_putstr(tgetstr(id, NULL));

__attribute__((unused))
static const char *CURSOR_SAVE    = "sc";

__attribute__((unused))
static const char *CURSOR_RECOVER = "rc";

__attribute__((unused))
static const char *CURSOR_LEFT    = "le";

__attribute__((unused))
static const char *CURSOR_RIGHT   = "nd";

__attribute__((unused))
static const char *LINE_DELETE    = "dl";

__attribute__((unused))
static const char *TERM_CLEAR     = "cl";

typedef struct termios termios_t;

typedef struct {
    char key;
    char *str;
    size_t cursor;
} line_t;

typedef struct file_list_s {
    unsigned char type;
    char *name;
    struct file_list_s *next;
} file_list_t;

void my_putchar(char c);
void print_prompt(void);
void my_putstr(char *str);
char *get_next_line(int fd);
char *my_strcat(char *buffer, char *str);

char *user_prompt(void);
void key_tab(line_t *line);
void key_suppr(line_t *line);
void move_left(line_t *line);
void history_up(line_t *line);
void move_right(line_t *line);
void clear_term(line_t *line);
void key_delete(line_t *line);
void key_actions(line_t *line);
void key_default(line_t *line);
void key_headcut(line_t *line);
void key_tailcut(line_t *line);
void reprint_prompt(char *str);
void history_down(line_t *line);
void key_wholecut(line_t *line);
void key_goto_head(line_t *line);
void key_goto_tail(line_t *line);
void key_print_help(line_t *line);
void escape_sequence(line_t *line);
void key_word_tailcut(line_t *line);
void key_word_headcut(line_t *line);
void key_wordgoto_head(line_t *line);
void key_wordgoto_tail(line_t *line);
void key_restore_buffer(line_t *line);
void del_char(char *str, size_t index);
char *buffer_copy(char *new_buffer, bool set);
line_t *global_line(line_t *new_line, bool set);
char *add_char(char *str, char c, size_t index);
void auto_complete(line_t *line, char *directory, char *file);
char **get_files(char *directory, char *file, size_t *file_count);
char *finish_readline(line_t *line, bool returning, termios_t *old_termios);
line_t *start_readline(termios_t *readable_termios, termios_t *old_termios);

#endif /* PROMPT_H_ */
