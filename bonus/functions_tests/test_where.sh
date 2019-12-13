##
## EPITECH PROJECT, 2019
## PSU_minishell1_2018
## File description:
## test_where
##

source ./utils/colors.sh
result_where_test=
total_where_test=

function test_where_correct_input {
    total_where_test=$((total_where_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "where $1" | ../mysh)
    local re=$(echo -e "where $1" | tcsh)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}where "; echo -n $cmd; echo -e "${BLU} >>${NC} where $1 \n${BLU}42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"

    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}where "; echo -n " $cmd "; echo -e "${BLU}>>${NC} where $1 \n${BLU}42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"
        result_where_test=$((result_where_test+=1))

    fi
}

function test_where_wrong_input {
    total_where_test=$((total_where_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "where $1" | ../mysh 2>&1> /dev/null)
    local re=$(echo -e "where $1" | tcsh 2>&1> /dev/null)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}where "; echo -n $cmd; echo -e "${BLU}>>${NC} where $1 \n${BLU}42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"

    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}where "; echo -n " $cmd "; echo -e "${BLU}>>${NC} where $1 \n${BLU}42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"
        result_where_test=$((result_where_test+=1))

    fi
}

function tests_where {
    echo -e "-------------------------------------------------"
    echo -e " [START OF ${CYAN}where${NC} TESTS]"
    echo -e "-------------------------------------------------"
    echo -e "${UL}Tests for correct input${NC}"
        test_where_correct_input "tree"
        test_where_correct_input "cd"
        test_where_correct_input "tree cd qzdz ./"
    echo -e "${UL}Tests for wrong inputs${NC}"
        test_where_wrong_input "/"
        test_where_wrong_input "qzd/qzd"
        test_where_wrong_input "qzd"
    echo -e "-------------------------------------------------"
    echo -e " [END OF ${CYAN}where${NC} TESTS: \
${BLU}[$result_where_test / $total_where_test]${NC} test(s) passed]"
    echo -e "-------------------------------------------------"
}
