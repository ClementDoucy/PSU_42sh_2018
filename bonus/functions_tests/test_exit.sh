##
## EPITECH PROJECT, 2019
## PSU_minishell1_2018
## File description:
## test_exit
##

source ./utils/colors.sh
result_exit_test=
total_exit_test=

function test_exit_correct_input {
    total_exit_test=$((total_exit_test+=1))

    echo -e "exit $1" | ../mysh &> /dev/null
    local my=$?
    echo -e "exit $1" | tcsh &> /dev/null
    local re=$?

    if [ $my != $re ]; then
        echo -e "${RED}[FAILURE]${NC}${BLU}: \
${NC}exit $1 ${BLU}>>${NC} exited $my instead of $re"

    else
        echo -e "${GRN}[SUCESS]${BLU}: \
${NC}exit $1 ${BLU}>>${NC} [$my | $re]"
        result_exit_test=$((result_exit_test+=1))

    fi
}

function test_exit_wrong_input {
    total_exit_test=$((total_exit_test+=1))
    local my=$(echo -e "exit $1" | ../mysh 2>&1> /dev/null)
    local re=$(echo -e "exit $1" | tcsh 2>&1> /dev/null)

    if [ "$my" != "$re" ]; then
        echo -e "${RED}[FAILURE]${NC}${BLU}: \
${NC}exit $1 ${BLU}>>${NC} \"$my\" instead of \"$re\""

    else
        echo -e "${GRN}[SUCESS]${BLU}: \
${NC}exit $1 ${BLU}>>${NC} [$my | $re]"
        result_exit_test=$((result_exit_test+=1))

    fi
}

function tests_exit {
    echo -e "--------------------------------"
    echo -e " [START OF ${CYAN}exit${NC} TESTS]"
    echo -e "--------------------------------"
    echo -e "${UL}Tests for correct inputs${NC}"
        test_exit_correct_input "084"
        test_exit_correct_input "025"
        test_exit_correct_input "000"
        test_exit_correct_input "255"
        test_exit_correct_input "300"
        test_exit_correct_input "-30"
        test_exit_correct_input "-255"
        test_exit_correct_input "255"
        test_exit_correct_input "-2837"
        test_exit_correct_input "-25"
        test_exit_correct_input ""
    echo -e "${UL}Tests for wrong inputs${NC}"
        test_exit_wrong_input "azer"
        test_exit_wrong_input "c123"
    echo -e "--------------------------------"
    echo -e " [END OF ${CYAN}exit${NC} TESTS: \
${BLU}[$result_exit_test / $total_exit_test]${NC} test(s) passed]"
    echo -e "--------------------------------"
}
