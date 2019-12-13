##
## EPITECH PROJECT, 2019
## PSU_minishell2_2018
## File description:
## test_pipe
##

source ./utils/colors.sh
result_pipe_test=
total_pipe_test=


function tests_pipe {
    echo -e "-------------------------------------------------"
    echo -e " [START OF ${CYAN}pipe${NC} TESTS]"
    echo -e "-------------------------------------------------"

    echo -e "${UL}Tests for correct inputs PWD${NC}"
    echo -e "${UL}Tests for wrong inputs${NC}"

    echo -e "-------------------------------------------------"
    echo -e " [END OF ${CYAN}pipe${NC} TESTS: \                                                 
${BLU}[$result_pipe_test / $total_pipe_test]${NC} test(s) passed]"
    echo -e "-------------------------------------------------"
}
