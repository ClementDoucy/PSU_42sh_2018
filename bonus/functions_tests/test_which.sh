##
## EPITECH PROJECT, 2019
## PSU_minishell1_2018
## File description:
## test_which
##

source ./utils/colors.sh
result_which_test=
total_which_test=

function test_which_correct_input {
    total_which_test=$((total_which_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "which $1" | ../mysh)
    local re=$(echo -e "which $1" | tcsh)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}which "; echo -n $cmd; echo -e "${BLU} >>${NC} which $1 \n${BLU}42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"

    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}which "; echo -n " $cmd "; echo -e "${BLU}>>${NC} which $1 \n${BLU}42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"
        result_which_test=$((result_which_test+=1))

    fi
}

function test_which_wrong_input {
    total_which_test=$((total_which_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "which $1" | ../mysh 2>&1> /dev/null)
    local re=$(echo -e "which $1" | tcsh 2>&1> /dev/null)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}which "; echo -n $cmd; echo -e "${BLU}>>${NC} which $1 \n${BLU}42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"

    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}which "; echo -n " $cmd "; echo -e "${BLU}>>${NC} which $1 \n${BLU}42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"
        result_which_test=$((result_which_test+=1))

    fi
}

function tests_which {
    echo -e "-------------------------------------------------"
    echo -e " [START OF ${CYAN}which${NC} TESTS]"
    echo -e "-------------------------------------------------"
    echo -e "${UL}Tests for correct input${NC}"
        test_which_correct_input "tree"
        test_which_correct_input "cd"
        test_which_correct_input "tree cd qzdqd ./qzd"
    echo -e "${UL}Tests for wrong inputs${NC}"
        test_which_wrong_input "../qzd"
        test_which_wrong_input "qzd/"
    echo -e "-------------------------------------------------"
    echo -e " [END OF ${CYAN}which${NC} TESTS: \
${BLU}[$result_which_test / $total_which_test]${NC} test(s) passed]"
    echo -e "-------------------------------------------------"
}
