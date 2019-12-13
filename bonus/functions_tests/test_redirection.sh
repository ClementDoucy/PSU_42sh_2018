##
## EPITECH PROJECT, 2019
## PSU_minishell1_2018
## File description:
## test_redirection
##

source ./utils/colors.sh
result_redirection_test=
total_redirection_test=

function test_redirection_correct_input {
    total_redirection_test=$((total_redirection_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "$1; cat toto" | ../mysh)
    local re=$(echo -e "$1; cat toto" | tcsh)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}redirection "; echo -n $cmd; echo -e "${BLU} >>${NC} redirection $1 \n${BLU}42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"

    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}redirection "; echo -n " $cmd "; echo -e "${BLU}>>${NC} redirection $1 \n${BLU}42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"
        result_redirection_test=$((result_redirection_test+=1))

    fi
}

function test_redirection_wrong_input {
    total_redirection_test=$((total_redirection_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "$1" | ../mysh 2>&1> /dev/null)
    local re=$(echo -e "$1" | tcsh 2>&1> /dev/null)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}redirection "; echo -n $cmd; echo -e "${BLU}>>${NC} redirection $1 \n${BLU}42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"

    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}redirection "; echo -n " $cmd "; echo -e "${BLU}>>${NC} redirection $1 \n${BLU}42sh\n${NC} $my \n${BLU}tcsh\n${NC} $re\n"
        result_redirection_test=$((result_redirection_test+=1))

    fi
}

function tests_redir {
    echo -e "-------------------------------------------------"
    echo -e " [START OF ${CYAN}redirection${NC} TESTS]"
    echo -e "-------------------------------------------------"
    echo -e "${UL}Tests for correct input${NC}"
        test_redirection_correct_input "ls > toto"
        test_redirection_correct_input "toto < ../Makefile"
        test_redirection_correct_input "cat < ../Makefile > toto"
    echo -e "${UL}Tests for wrong inputs${NC}"
        test_redirection_wrong_input "cat < Makefile > toto"
        test_redirection_wrong_input "cats < ../Makefile > toto"
        test_redirection_wrong_input "cat <<<<<<< ../Makefile > toto"
        test_redirection_wrong_input "cat <> ../Makefile > toto"
        test_redirection_wrong_input "cat >>>>>>>>>>>>>>>>>>>> ../Makefile > toto"
        test_redirection_wrong_input "cat toto > ../Makefile > toto"
    echo -e "-------------------------------------------------"
    echo -e " [END OF ${CYAN}redirection${NC} TESTS: \
${BLU}[$result_redirection_test / $total_redirection_test]${NC} test(s) passed]"
    echo -e "-------------------------------------------------"
}
