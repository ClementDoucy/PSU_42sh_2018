/*
** EPITECH PROJECT, 2019
** conditionnal_operator.c
** File description:
** manage conditionnal operator (&&, ||)
*/

#include "mysh.h"

static bool next_must_be_exec(int status, cond_oprt_t oprt)
{
    switch (oprt) {
    case AND:
        if (status)
            return false;
        break;
    case OR:
        if (!status)
            return false;
        break;
    case END_COND_OPRT:
        break;
    }
    return true;
}

void manage_conditionnal(char **cmd_arr, cond_oprt_t *cond, char ***env,
    int *status)
{
    bin_str_t *root = NULL;
    int oprt = 0;

    *status = 0;
    for (int i = 0; cmd_arr[i]; i++) {
        if (cond && i && !next_must_be_exec(*status, cond[oprt])) {
            *status = 0;
            continue;
        } if (is_simple_command(cmd_arr[i]) && !is_empty_line(cmd_arr[i]))
            launch_cmd(cmd_arr[i], env, status);
        else if (!is_empty_line(cmd_arr[i])) {
            if (!(root = gen_tree_cmd(cmd_arr[i]))) {
                my_print(2, "Error: malloc failed.\n");
                *status = 1;
                return;
            }
            exec_all(root, env, status);
            destroy_tree(root);
        }
        oprt += (i ? 1 : 0);
    }
}
