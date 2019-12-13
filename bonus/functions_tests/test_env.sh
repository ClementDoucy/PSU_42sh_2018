##
## EPITECH PROJECT, 2019
## PSU_minishell1_2018
## File description:
## test_env
##

source ./utils/colors.sh
result_env_test=
total_env_test=

function test_env_correct_input {
    total_env_test=$((total_env_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "env $1\n pwd" | ../mysh)
    local re=$(echo -e "env $1\n pwd" | tcsh)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}env"; echo -n $cmd; echo -e "${BLU}>>${NC} chdir to $my instead of $re"

    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}env"; echo -n " $cmd "; echo -e "${BLU}>>${NC} [$my | $re]"
        result_env_test=$((result_env_test+=1))

    fi
}

function test_env_wrong_input {
    total_env_test=$((total_env_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "$1" | ../mysh 2>&1> /dev/null)
    local re=$(echo -e "$1" | tcsh 2>&1> /dev/null)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}"; echo -n $cmd; echo -e "${BLU}>>${NC} \"$my\" instead of \"$re\""

    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}"; echo -n " $cmd "; echo -e "${BLU}>>${NC} [$my | $re]"
        result_env_test=$((result_env_test+=1))

    fi
}

function tests_env {
    echo -e "-------------------------------------------------"
    echo -e " [START OF ${CYAN}env${NC} TESTS]"
    echo -e "-------------------------------------------------"
    echo -e "${UL}Tests for wrong inputs setenv${NC}"
        test_env_wrong_input "setenv a b c"
        test_env_wrong_input "setenv ="
        test_env_wrong_input "setenv 123="
        test_env_wrong_input "setenv a/~"
    echo -e "${UL}Tests for wrong inputs unsetenv${NC}"
        test_env_wrong_input "unsetenv"
    echo -e "-------------------------------------------------"
    echo -e " [END OF ${CYAN}env${NC} TESTS: \
${BLU}[$result_env_test / $total_env_test]${NC} test(s) passed]"
    echo -e "-------------------------------------------------"
}
