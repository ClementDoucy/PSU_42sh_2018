/*
** EPITECH PROJECT, 2019
** mysh_2_test.c
** File description:
** redirection tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "mysh.h"

void redirect_all_std(void);

Test(pipe_test, pipe_1, .init = redirect_all_std)
{
    FILE *f = NULL;
    char **env = malloc(sizeof(char *) * 2);
    int status = 0;
    char *cmd = strdup("ls include | grep print | cut -c 3-8 |"
        "cat -e | head -n 3 > data");

    *env = strdup("PATH=/bin");
    *(env + 1) = NULL;
    launch_cmd(cmd, &env, &status);
    f = fopen("./data", "r");
    cr_assert_file_contents_eq_str(f, "_print$\n");
    free(cmd);
    cmd = strdup("rm data");
    launch_cmd(cmd, &env, &status);
}

Test(semi_test, semi_1, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 2);
    int status = 0;
    char *cmd = strdup(";   \t\t    \t\t;;; ;; ;;  \techo\t     \t hello"
        "\t   \t | cat     \t-e    >\t\t\t\tworld  \t;    \t;;;; \t"
        ";;; ; ;\t\t;   cat  \t\tworld ;;;; \trm   world \t   \t  ;;"
        ";;  \t;; \t    ls \t\t  |    grep  world\t;;;  \t;;;\t; ;; \n");

    *env = strdup("PATH=/bin");
    *(env + 1) = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_stdout_eq_str("hello$\n");
}

Test(cd_test, cd_test_1, .init = redirect_all_std)
{
    int status = 0;
    char *cmd = strdup("cd / ; pwd ; cd bin ; pwd ; cd - ; pwd ; cd - ; pwd");
    char **env = malloc(sizeof(char *) * 2);

    *env = strdup("PATH=/bin");
    *(env + 1) = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_stdout_eq_str("/\n/usr/bin\n/\n/usr/bin\n");
}

Test(my_print_test, my_print_test_1, .init = redirect_all_std)
{
    ssize_t value = my_print(1, "%d%swolrd%sjddza%d%s%d%sdzadza%d%d%s\n",
        42, "hello", "world", 3200032, "titi", -73917, "dkakdalklk",
        83177, -3000103, "tatatoto");
    cr_assert_eq(value, 77);
    cr_assert_stdout_eq_str("42hellowolrdworldjddza3200032titi-"
        "73917dkakdalklkdzadza83177-3000103tatatoto\n");
}

Test(input_redir, input_1, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 2);
    char *cmd = strdup("ls > toto ; cat < toto | grep Makefile"
        "| cat -e ; rm toto");
    int status = 0;

    *env = strdup("PATH=/bin");
    *(env + 1) = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_stdout_eq_str("Makefile$\n");
}

Test(input_redir, input_2, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 2);
    char *cmd = strdup("echo hello world > tata ; cat < tata ; rm tata");
    int status = 0;

    *env = strdup("PATH=/bin/");
    *(env + 1) = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_stdout_eq_str("hello world\n");
}

Test(input_redir, input_3, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 2);
    char *cmd = strdup("echo hello world > titi ; cat < titi | "
        "grep world | cat -e >> titi ; cat titi ; rm titi");
    int status = 0;

    *env = strdup("PATH=/bin/");
    *(env + 1) = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_stdout_eq_str("hello world\nhello world$\n");
}

Test(input_redir, input_4, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 2);
    char *cmd = strdup("echo hello world > tutu ; cat < tutu > tyty"
        "; cat tyty ; rm tyty ; cat tutu ; rm tutu ;");
    int status = 0;

    *env = strdup("PATH=/bin/");
    *(env + 1) = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_stdout_eq_str("hello world\nhello world\n");
}

Test(input_redir_error, input_err_1, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 2);
    char *cmd = strdup("cat < qsdf");
    int status = 0;

    *env = strdup("PATH=/bin/");
    *(env + 1) = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_stderr_eq_str("qsdf: No such file or directory.\n");
}

Test(input_redir_error, input_err_2, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 2);
    char *cmd = strdup("cat < qsdf | echo hello | cat -e");
    int status = 0;

    *env = strdup("PATH=/bin/");
    *(env + 1) = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_stderr_eq_str("qsdf: No such file or directory.\n");
    cr_assert_stdout_eq_str("hello$\n");
}

Test(input_and_output_redir, input_an_ouput_1, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 2);
    char *cmd = strdup("echo hello > abc ; cat < abc > cba "
        "; rm abc ; cat < cba ; rm cba");
    int status = 0;

    *env = strdup("PATH=/bin/");
    *(env + 1) = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_stdout_eq_str("hello\n");
}
