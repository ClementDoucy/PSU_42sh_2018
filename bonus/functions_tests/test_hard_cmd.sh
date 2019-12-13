##
## EPITECH PROJECT, 2019
## PSU_minishell1_2018
## File description:
## test_set
##

source ./utils/colors.sh
result_hard_cmd_test=
total_hard_cmd_test=

function test_hard_cmd_correct_input {
    total_hard_cmd_test=$((total_hard_cmd_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "$1\n" | ../mysh)
    local re=$(echo -e "$1\n" | tcsh)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}"; echo -n $cmd; echo -e "${BLU} >> ${NC} $1 :
\n${BLU}42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"

    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}"; echo -n " $cmd "; echo -e "${BLU} >> ${NC} $1
\n${BLU}42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"
        result_hard_cmd_test=$((result_hard_cmd_test+=1))
    fi
}

function test_hard_cmd_wrong_input {
    total_hard_cmd_test=$((total_hard_cmd_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "$1\n" | ../mysh 2>&1> /dev/null)
    local re=$(echo -e "$1\n" | tcsh 2>&1> /dev/null)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}"; echo -n $cmd; echo -e "${BLU} >> ${NC}
\n${BLU} 42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"
    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}"; echo -n " $cmd "; echo -e "${BLU} >> ${NC} $1 \n${BLU}42sh\n${NC} $my
\n${BLU}tcsh\n${NC} $re\n"
        result_hard_cmd_test=$((result_hard_cmd_test+=1))
    fi
}

function tests_hard_cmd {
    echo -e "-------------------------------------------------"
    echo -e " [START OF ${CYAN}Hard Cmd${NC} TESTS]"
    echo -e "-------------------------------------------------"
    echo -e "${UL}Tests for correct inputs${NC}"
        test_hard_cmd_correct_input "ls -l | cat -e"
        test_hard_cmd_correct_input "ls -l | wc -l | cat -e > toto"
        test_hard_cmd_correct_input "ls -l | wc -l | cat -e > toto ; cat < ../Makefile > toto; cat toto | grep -r all"
    echo -e "${UL}Tests for wrong inputs${NC}"
        test_hard_cmd_wrong_input "toto"
        test_hard_cmd_wrong_input "ls -l | wc -l | cat -e > toto ; cat < ../Makefile > toto; cat toto | grep -r all; toto"
    echo -e "-------------------------------------------------"
    echo -e " [END OF ${CYAN}Hard Cmd${NC} TESTS: \
${BLU}[$result_hard_cmd_test / $total_hard_cmd_test]${NC} test(s) passed]"
    echo -e "-------------------------------------------------"
}
