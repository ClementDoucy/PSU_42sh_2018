##
## EPITECH PROJECT, 2019
## PSU_minishell1_2018
## File description:
## test_execve
##

source ./utils/colors.sh
result_execve_test=
total_execve_test=

function test_execve_correct_input {
    total_execve_test=$((total_execve_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "$1" | ../mysh)
    local re=$(echo -e "$1" | tcsh)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}"; echo -n $cmd; echo -e "${BLU}>>${NC} chdir to $my instead of $re"

    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}"; echo -n " $cmd "; echo -e "${BLU}>>${NC} [$my | $re]"
        result_execve_test=$((result_execve_test+=1))

    fi
}

function test_execve_wrong_input {
    total_execve_test=$((total_execve_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "$1" | ../mysh 2>&1> /dev/null)
    local re=$(echo -e "$1" | tcsh 2>&1> /dev/null)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}"; echo -n $cmd; echo -e "${BLU}>>${NC} \"$my\" instead of \"$re\""

    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}"; echo -n " $cmd "; echo -e "${BLU}>>${NC} [$my | $re]"
        result_execve_test=$((result_execve_test+=1))

    fi
}

function tests_execve {
    echo -e "-------------------------------------------------"
    echo -e " [START OF ${CYAN}execve${NC} TESTS]"
    echo -e "-------------------------------------------------"
    echo -e "${UL}Tests for correct inputs${NC}"
        test_execve_correct_input "ls ./lib"
        test_execve_correct_input "wc test_main.sh"
        test_execve_correct_input "cd; echo bonjour; "
    echo -e "${UL}Tests for wrong inputs${NC}"
        test_execve_wrong_input "ls ./azeraze"
        test_execve_wrong_input "./crash/segfault"
        test_execve_wrong_input "./crash/divbyzero"
        test_execve_wrong_input "./crash/plus/segfault"
        test_execve_wrong_input "./crash/plus/divbyzero"
        test_execve_wrong_input "./crash"
        test_execve_wrong_input "foo"
        test_execve_wrong_input "./crash/plus/sigbus"
        test_execve_wrong_input "./crash/sigbus"
        test_execve_wrong_input "./crash/binnotcompatible"
    echo -e "-------------------------------------------------"
    echo -e " [END OF ${CYAN}execve${NC} TESTS: \
${BLU}[$result_execve_test / $total_execve_test]${NC} test(s) passed]"
    echo -e "-------------------------------------------------"
}
