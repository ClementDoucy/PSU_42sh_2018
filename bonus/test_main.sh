##
## EPITECH PROJECT, 2019
## PSU_minishell1_2018
## File description:
## test_main
##

source ./lib/test_lib.sh

export LANG en_us.UTF8

make -C ../
mv ../42sh ../mysh

tests_exit
echo
tests_cd
echo
tests_execve
echo
tests_format
echo
tests_env
echo
tests_pipe
echo
tests_redir
echo
tests_which
echo
tests_where
echo
tests_hard_cmd
echo
tests_conditionnal
echo

total=$((total_cd_test+total_exit_test+total_execve_test+total_format_test+total_env_test+
        total_pipe_test+total_redirection_test+total_set_test+total_which_test+total_hard_cmd_test+total_where_test+total_conditionnal_test))
ok=$((result_cd_test+result_exit_test+result_execve_test+result_format_test+result_env_test+
     result_pipe_test+result_redirection_test+result_set_test+result_which_test+result_hard_cmd_test+result_where_test+result_conditionnal_test))

echo -e
echo -e "---------------------------------"
echo -e " [TOTAL TESTS PASSED: ${BLU}[$ok / $total]${NC}]"
echo -e "---------------------------------"

rm ../mysh
rm toto
make -C ../ fclean
