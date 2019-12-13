/*
** EPITECH PROJECT, 2019
** test.c
** File description:
** unit tests for minishell1
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "mysh.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(test_1, are_eq_str)
{
    char *s1 = "toto";
    char *s2 = "     toto     ";
    char *s3 = "       toto     ";
    char *s4 = "toto tata";
    char *s5 = "      toto              tata       ";
    char *s6 = "tata";
    char *s7 = "      tooto       ";

    cr_assert_eq(are_eq_str(s1, s1), true);
    cr_assert_eq(are_eq_str(s1, s2), true);
    cr_assert_eq(are_eq_str(s2, s3), true);
    cr_assert_eq(are_eq_str(s4, s1), true);
    cr_assert_eq(are_eq_str(s5, s2), true);
    cr_assert_eq(are_eq_str(s6, s1), false);
    cr_assert_eq(are_eq_str(s7, s3), false);
}

Test(test_2, are_eq_var)
{
    cr_assert_eq(are_eq_var("PATH=/bin/", "PATH"), true);
    cr_assert_eq(are_eq_var("HOM=/home/cdoucy/", "HOME"), false);
}

Test(test_3, is_var_exist)
{
    char **env = malloc(sizeof(char *) * 3);

    env[0] = my_strdup("HOME=/home/cdoucy/");
    env[1] = my_strdup("PATH=/bin/");
    env[2] = my_strdup("PWD=/home/cdoucy/Delivery");
    env[3] = NULL;

    cr_assert_eq(is_var_exist("PATH", env), 1);
    cr_assert_eq(is_var_exist("LANG", env), -1);
}

Test(test_4, is_empty_line)
{
    cr_assert_eq(is_empty_line("    \t    \t\n"), true);
    cr_assert_eq(is_empty_line("     \t     a\t\n"), false);
}

Test(test_5, get_path_1)
{
    char **env = malloc(sizeof(char *));
    char **bin_path = NULL;

    env[0] = my_strdup("PATH=/home/cdoucy/bin:/usr/local/bin:/usr/local/bin:"
        "/usr/bin:/bin:/home/cdoucy/bin:/usr/local/sbin:/usr/sbin");
    env[1] = NULL;
    bin_path = get_path(env, 0);
    cr_assert_str_eq(bin_path[0], "/home/cdoucy/bin");
    cr_assert_str_eq(bin_path[1], "/usr/local/bin");
    cr_assert_str_eq(bin_path[2], "/usr/local/bin");
    cr_assert_str_eq(bin_path[3], "/usr/bin");
    cr_assert_str_eq(bin_path[4], "/bin");
    cr_assert_str_eq(bin_path[5], "/home/cdoucy/bin");
    cr_assert_str_eq(bin_path[6], "/usr/local/sbin");
    cr_assert_str_eq(bin_path[7], "/usr/sbin");
    cr_assert_eq(bin_path[8], NULL);
}

Test(test_6, get_path_2)
{
    char **env = malloc(sizeof(char *));
    char **bin_path = NULL;

    env[0] = my_strdup("PATH==/home/cdoucy/bin::/usr/local/bin::/usr/local/"
        "bin:::/usr/bin:::/bin:::/home/cdoucy/bin::"
        "/usr/local/sbin::::/usr/sbin::");
    env[1] = NULL;
    bin_path = get_path(env, 0);
    cr_assert_str_eq(bin_path[0], "/home/cdoucy/bin");
    cr_assert_str_eq(bin_path[1], "/usr/local/bin");
    cr_assert_str_eq(bin_path[2], "/usr/local/bin");
    cr_assert_str_eq(bin_path[3], "/usr/bin");
    cr_assert_str_eq(bin_path[4], "/bin");
    cr_assert_str_eq(bin_path[5], "/home/cdoucy/bin");
    cr_assert_str_eq(bin_path[6], "/usr/local/sbin");
    cr_assert_str_eq(bin_path[7], "/usr/sbin");
    cr_assert_eq(bin_path[8], NULL);
}

Test(test_7, env, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 4);
    char *expected = "HOME=/home/cdoucy/\nPATH=/bin/\n"
        "PWD=/home/cdoucy/Delivery\n";

    env[0] = my_strdup("HOME=/home/cdoucy/");
    env[1] = my_strdup("PATH=/bin/");
    env[2] = my_strdup("PWD=/home/cdoucy/Delivery");
    env[3] = NULL;
    launch_cmd("env", &env, 0);
    cr_assert_stdout_eq_str(expected);
}

Test(Test_8, setenv_1, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 4);
    char *expected = "HOME=/home/cdoucy/\nPATH=/bin/\n"
        "PWD=/home/cdoucy/Delivery\n";
    char *cmd = my_strdup("setenv");

    env[0] = my_strdup("HOME=/home/cdoucy/");
    env[1] = my_strdup("PATH=/bin/");
    env[2] = my_strdup("PWD=/home/cdoucy/Delivery");
    env[3] = NULL;
    launch_cmd(cmd, &env, 0);
    cr_assert_stdout_eq_str(expected);
}

Test(Test_9, setenv_2, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 4);
    char *expected = "setenv: Too many arguments.\n";
    char *cmd = my_strdup("setenv a b c\n");
    int status = 0;

    env[0] = my_strdup("HOME=/home/cdoucy/");
    env[1] = my_strdup("PATH=/bin/");
    env[2] = my_strdup("PWD=/home/cdoucy/Delivery");
    env[3] = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_eq(status, 1);
    cr_assert_stderr_eq_str(expected);
}

Test(Test_10, setenv_3)
{
    char **env = malloc(sizeof(char *) * 4);
    char *expected = "setenv: Too many arguments.\n";
    char *cmd = my_strdup("setenv toto tata\n");

    env[0] = my_strdup("HOME=/home/cdoucy/");
    env[1] = my_strdup("PATH=/bin/");
    env[2] = my_strdup("PWD=/home/cdoucy/Delivery");
    env[3] = NULL;
    launch_cmd(cmd, &env, 0);
    cr_assert_str_eq(env[0], "HOME=/home/cdoucy/");
    cr_assert_str_eq(env[1], "PATH=/bin/");
    cr_assert_str_eq(env[2], "PWD=/home/cdoucy/Delivery");
    cr_assert_str_eq(env[3], "toto=tata");
    cr_assert_eq(env[4], NULL);
}

Test(Test_11, setenv_4)
{
    char **env = malloc(sizeof(char *) * 4);
    char *expected = "setenv: Too many arguments.\n";
    char *cmd = my_strdup("setenv toto\n");

    env[0] = my_strdup("HOME=/home/cdoucy/");
    env[1] = my_strdup("PATH=/bin/");
    env[2] = my_strdup("PWD=/home/cdoucy/Delivery");
    env[3] = NULL;
    launch_cmd(cmd, &env, 0);
    cr_assert_str_eq(env[0], "HOME=/home/cdoucy/");
    cr_assert_str_eq(env[1], "PATH=/bin/");
    cr_assert_str_eq(env[2], "PWD=/home/cdoucy/Delivery");
    cr_assert_str_eq(env[3], "toto=");
    cr_assert_eq(env[4], NULL);
}

Test(Test_12, setenv_5, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 4);
    char *expected = "setenv: Variable name must begin with a letter.\n";
    char *cmd = my_strdup("setenv 1toto\n");
    int status = 0;

    env[0] = my_strdup("HOME=/home/cdoucy/");
    env[1] = my_strdup("PATH=/bin/");
    env[2] = my_strdup("PWD=/home/cdoucy/Delivery");
    env[3] = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_eq(status, 1);
    cr_assert_stderr_eq_str(expected);
}

Test(Test_13, setenv_6, .init = redirect_all_std)
{
    char **env = malloc(sizeof(char *) * 4);
    char *expected = "setenv: Variable name must contain "
        "alphanumeric characters.\n";
    char *cmd = my_strdup("setenv to?to tata\n");
    int status = 0;

    env[0] = my_strdup("HOME=/home/cdoucy/");
    env[1] = my_strdup("PATH=/bin/");
    env[2] = my_strdup("PWD=/home/cdoucy/Delivery");
    env[3] = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_eq(status, 1);
    cr_assert_stderr_eq_str(expected);
}

Test(Test_14, unsetenv_1, .init = redirect_all_std)
{
    int status = 0;
    char **env = NULL;
    char *cmd = my_strdup("unsetenv\n");
    char *expected = "unsetenv: Too few arguments.\n";

    launch_cmd(cmd, &env, &status);
    cr_assert_eq(status, 1);
    cr_assert_stderr_eq_str(expected);
}

Test(Test_15, unsetenv_2)
{
    int status = 0;
    char **env = malloc(sizeof(char *) * 6);
    char *cmd = my_strdup("unsetenv tutu tata toto hello\n");

    env[0] = my_strdup("tata=");
    env[1] = my_strdup("titi=toto");
    env[2] = my_strdup("hello=world");
    env[3] = my_strdup("a=b");
    env[4] = my_strdup("tutu=toto");
    env[5] = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_str_eq(env[0], "titi=toto");
    cr_assert_str_eq(env[1], "a=b");
    cr_assert_eq(env[2], NULL);
}

Test(Test_16, setenv_7)
{
    char **env = malloc(sizeof(char *) * 5);
    char *expected = "setenv: Too many arguments.\n";
    char *cmd = my_strdup("setenv toto tata\n");

    env[0] = my_strdup("HOME=/home/cdoucy/");
    env[1] = my_strdup("toto=");
    env[2] = my_strdup("PATH=/bin/");
    env[3] = my_strdup("PWD=/home/cdoucy/Delivery");
    env[4] = NULL;
    launch_cmd(cmd, &env, 0);
    cr_assert_str_eq(env[0], "HOME=/home/cdoucy/");
    cr_assert_str_eq(env[1], "toto=tata");
    cr_assert_str_eq(env[2], "PATH=/bin/");
    cr_assert_str_eq(env[3], "PWD=/home/cdoucy/Delivery");
    cr_assert_eq(env[4], NULL);
}

Test(Test_17, setenv_8)
{
    char **env = malloc(sizeof(char *) * 5);
    char *expected = "setenv: Too many arguments.\n";
    char *cmd = my_strdup("setenv toto tata\n");

    env[0] = my_strdup("HOME=/home/cdoucy/");
    env[1] = my_strdup("toto=titi");
    env[2] = my_strdup("PATH=/bin/");
    env[3] = my_strdup("PWD=/home/cdoucy/Delivery");
    env[4] = NULL;
    launch_cmd(cmd, &env, 0);
    cr_assert_str_eq(env[0], "HOME=/home/cdoucy/");
    cr_assert_str_eq(env[1], "toto=tata");
    cr_assert_str_eq(env[2], "PATH=/bin/");
    cr_assert_str_eq(env[3], "PWD=/home/cdoucy/Delivery");
    cr_assert_eq(env[4], NULL);
}

Test(Test_18, launch_argv)
{
    char *cmd = my_strdup("  \tls     \t\t   -R    \t  include  \t  -t   \n");
    char **argv = launch_argv(cmd);

    cr_assert_str_eq(argv[0], "ls");
    cr_assert_str_eq(argv[1], "-R");
    cr_assert_str_eq(argv[2], "include");
    cr_assert_str_eq(argv[3], "-t");
    cr_assert_eq(argv[4], NULL);
}

Test(Test_19, binary_research)
{
    char **bin_path = malloc(sizeof(char *) * 2);
    char *binary = NULL;

    bin_path[0] = my_strdup("/usr/bin");
    bin_path[1] = NULL;
    binary = launch_research("dadza\n", bin_path);
    cr_assert_eq(binary, NULL);
}

Test(Test_20, exit_1, .init = redirect_all_std)
{
    char *cmd = my_strdup("exit 1 1\n");
    char **env = NULL;

    launch_cmd(cmd, &env, 0);
    cr_assert_stderr_eq_str("exit: Expression Syntax.\n");
}

Test(Test_21, exit_2, .init = redirect_all_std, .exit_code = 10)
{
    char *cmd = my_strdup("exit 10\n");
    char **env = malloc(sizeof(char *) * 2);
    int status = 0;

    env[0] = my_strdup("toto=tata");
    env[1] = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_stdout_eq_str("exit\n");
}

Test(Test_22, exit_3, .init = redirect_all_std)
{
    char *cmd = my_strdup("exit -18a6\n");
    char **env = malloc(sizeof(char *) * 2);
    int status = 0;

    env[0] = my_strdup("toto=tata");
    env[1] = NULL;
    launch_cmd(cmd, &env, &status);
    cr_assert_stderr_eq_str("exit: Expression Syntax.\n");
}
