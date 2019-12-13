/*
** EPITECH PROJECT, 2019
** mysh.h
** File description:
** header file for minishell
*/

#ifndef MYSH_H_
#define MYSH_H_

#define PIPE(a) ((a)==('|'))
#define SEMI(a) ((a)==(';'))
#define SUP(a) ((a)==('>'))
#define INF(a) ((a)==('<'))
#define IS_AND(a) ((*a)==('&') && (*(a + 1))==('&'))
#define IS_OR(a) ((*a)==('|') && (*(a + 1))==('|'))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include "tools.h"
#include "my_print.h"

typedef struct dirent dir_t;
typedef struct binary_str bin_str_t;
typedef struct builtin_struct builtin_t;
typedef struct double_cmd pipe_t;
typedef struct shell shell_t;
typedef enum cond_oprt cond_oprt_t;

struct binary_str
{
    char *str;
    bin_str_t *left;
    bin_str_t *right;
};

struct builtin_struct
{
    void (*fn_ptr)(char *, char ***, int *);
    char *builtin;
};

struct shell
{
    char ***env;
    int *status;
};

typedef enum
{
    SET,
    GET,
    UNSET,
    PRINT,
    UP,
    DOWN,
} cmd_t;

enum cond_oprt {
    AND,
    OR,
    END_COND_OPRT
};

char *prompt(void);
void launch(char **);
char *run_shell(int *);
bool are_eq_str(char *, char *);
void launch_cmd(char *, char ***, int *);
void launch_exit(char *, char ***, int *);
void launch_process(char *, char **, int *);
char **launch_argv(char *);
size_t compute_size_argv(char *);
char *arg_dup(char *);
char **get_argv(char *, size_t);
void launch_setenv(char *, char ***, int *);
char **add_var(char *, char **, int *);
bool are_eq_var(char *, char *);
int is_var_exist(char *, char **);
char **add_var_and_param(char *, char **, int *);
void launch_unsetenv(char *, char ***, int *);
char **reduct_env(char *, char **);
char *launch_bin(char *, char **);
char **get_path(char **, int);
size_t compute_size_path(char *);
char *path_dup(char *);
char *launch_research(char *, char **);
bool is_empty_line(char *);
void launch_cd(char *, char ***, int *);
char *get_env_param(char **, char *);
int change_dir(char **, char *, char *);
bool is_number(char *);
bool check_crash(int *);
int launch_cd_2(size_t, char *);
int change_dir_2(char **, char *, char *);
bool is_path_valid(char *, size_t, char *, char *);
bool is_valid_var(char *, int *);
bool is_file_or_dir(char *);
void check_child_error(char *);
bool is_filepath(char *);
void parse_command(char *, char ***, int *);
ssize_t cmd_len(char *);
char **cmd_to_double_array(char *, size_t);
char *cmd_dup(char *);
int launch_pipe(pipe_t *, char **, int *, int);
int **gen_pipefd(char **);
void manage_child(char *, char **);
char **str_split(const char *, char);
size_t split_len(const char *, char);
char *dup_until_delim(const char *, char);
char *str_clean(char *);
char **cmd_split(char *);
bin_str_t *init_bin_str(char *);
void connect_bin_str(bin_str_t *, bin_str_t *, bool);
void get_old_pwd(char **, char **);
bool is_path_valid_2(char **, char *, char *);
bool is_simple_command(char *);
bin_str_t *gen_tree_cmd(char *);
char *get_cmd(char *);
char *get_operator(char *);
bin_str_t *build_tree(char *);
void print_tree(bin_str_t *);
void destroy_tree(bin_str_t *);
bool check_redir_error(char *);
void exec_all(bin_str_t *, char ***, int *);
void exec_pipe(char *, char **, int *, int *);
void scan_tree(bin_str_t *, char **, int *, int *);
size_t pipe_len(bin_str_t *);
void run_pipe(bin_str_t *, char ***, int *, int *);
bool check_right_redir(char *, int *);
void redir_to_file(bin_str_t *, char **, int *, int *);
bool check_file_redir_error(bin_str_t *, int *);
void manage_semi(char **, char ***, int *);
void append_redir_to_file(bin_str_t *, char **, int *, int *);
bool check_input_redir_error(bin_str_t *, int *);
int redir_from_file(bin_str_t *, int *);
void my_str_swap(char **, char **);
bin_str_t *start_redirection(bin_str_t *, int *, int *);
void end_redir(bin_str_t **, int, int *, shell_t);
int get_case(bin_str_t *, bin_str_t *);
int double_left_redir(char *);
bool check_operator_error(char *);
void catch_sigint(int);
void print_prompt(void);
bool is_builtin(char *);
void exec_last_pipe(char *, char ***, int *, int *);
void last_redir_to_file(bin_str_t *, char ***, int *, int *);
void last_append_redir_to_file(bin_str_t *, char ***, int *, int *);
void launch_which(char *, char ***, int *);
void launch_where(char *, char ***, int *);
void launch_echo(char *, char ***, int *);
char *gestion_alias(char *cmd, int *status, char *name, cmd_t type);
char *gestion_history(char *cmd, char ***env, int *status, cmd_t);
char **init_var(void);
char **copy_var(char **var_ini, int add);
char **unset(char *name, char **var);
void clean_var(char **var);
void printvar(char **var);
char *getvar(char **var, char *search, int *index);
int my_count_tab(char **var_ini);
void clean_var(char **var);
char *gestion_var(char *key, char *value, int overwrite, cmd_t cmd);
int gestion_local(char *str);
char *init_new_var(char *value, char *name);
void my_close(int *);
void manage_conditionnal(char **, cond_oprt_t *, char ***, int *);
char **sep_cond_oprt(char *cmd, cond_oprt_t **state);
void destroy_2d_2allocs(void **arr);

#endif
