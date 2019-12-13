##
## EPITECH PROJECT, 2019
## test_conditionnal.sh
## File description:
## test condition
##

source ./utils/colors.sh
result_conditionnal_test=
total_conditionnal_test=

function test_conditionnal_basic {
    total_conditionnal_test=$((total_conditionnal_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "$1" | ../mysh)
    local re=$(echo -e "$1" | tcsh)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}"; echo -n $cmd; echo -e "${BLU}>>${NC} \"$my\" instead of \"$re\""

    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}"; echo -n " $cmd "; echo -e "${BLU}>>${NC} [$my | $re]"
        result_conditionnal_test=$((result_conditionnal_test+=1))

    fi
}

function tests_conditionnal {
    echo -e "-------------------------------------------------"
    echo -e " [START OF ${CYAN}conditionnal${NC} TESTS]"
    echo -e "-------------------------------------------------"
    echo -e "${UL}Tests for conditionnal basic${NC}"
    test_conditionnal_basic "ls && echo hello"
    test_conditionnal_basic "ls || echo hello"
    test_conditionnal_basic "ls || echo hello && cat lib"
    test_conditionnal_basic "ls && echo hello || cat lib"
    test_conditionnal_basic "ls | crash/segfault && echo hello || cat lib"
    test_conditionnal_basic "ls | crash/segfault || echo hello && cat lib"
    test_conditionnal_basic "ls | crash/segfault || echo hello || cat lib"
    test_conditionnal_basic "ls | crash/segfault && echo hello && cat lib"
    test_conditionnal_basic "ls < dza || echo hello && dzadza && echo world"
    test_conditionnal_basic "ls dzadza | cat -e || echo hello && cat lib || ls crash > data && rm data"
    echo -e " [END OF ${CYAN}conditionnal${NC} TESTS: \
${BLU}[$result_conditionnal_test / $total_conditionnal_test]${NC} test(s) passed]"
    echo -e "-------------------------------------------------"
}