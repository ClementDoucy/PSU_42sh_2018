/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** sep_cmd
*/

#include <ctype.h>
#include <stdbool.h>
#include "parse.h"

static const char *IGN = "'\"`";

static bool get_esc_state(bool in_state[3], char c, int *status, int *par)
{
    bool esc_state = 0;

    for (size_t i = 0; IGN[i] != '\0'; i++) {
        in_state[i] = (c == IGN[i] ? !in_state[i] : in_state[i]);
        esc_state |= in_state[i];
    }
    if (c == '(' && esc_state == false)
        *par += 1;
    if (c == ')' && esc_state == false)
        *par -= 1;
    if (*par < 0)
        *status = 1;
    if (*par > 0)
        return true;
    return esc_state;
}

static void sepcmds_err_gesture(bool in_state[3], int par, int *status)
{
    for (size_t i = 0; i < 3; i++) {
        if (in_state[i] == true) {
            fprintf(stderr, "Unmatched '%c'.\n", IGN[i]);
            *status = 1;
            return;
        }
    }
    if (par != 0) {
        fprintf(stderr, "Too many %c's.\n", (par < 0) ? ')' : '(');
        *status = 1;
    }
}

size_t sepcmds(char *cmd, int *status)
{
    size_t nb_of_cmds = 0;
    int par = 0;
    bool in_state[3] = {0};
    bool esc_state = false;

    for (nb_of_cmds++; *cmd == CMD_SEP || isspace(*cmd); *cmd++ = '\0');
    for (; *cmd != '\0'; esc_state = false) {
        if (*cmd == ESC && in_state[0] == false) {
            cmd++;
            continue;
        }
        esc_state = get_esc_state(in_state, *cmd, status, &par);
        if (esc_state == false && *cmd == CMD_SEP) {
            nb_of_cmds += 1;
            for (; *cmd == CMD_SEP; *cmd = '\0', cmd++);
        } else {
            (*cmd) ? cmd++ : cmd;
        }
    }
    sepcmds_err_gesture(in_state, par, status);
    return nb_of_cmds;
}