##
## EPITECH PROJECT, 2019
## PSU_minishell1_2018
## File description:
## test_cd
##

source ./utils/colors.sh
result_cd_test=
total_cd_test=

function test_cd_correct_input {
    total_cd_test=$((total_cd_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "cd $1\n pwd" | ../mysh)
    local re=$(echo -e "cd $1\n pwd" | tcsh)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}cd"; echo -n $cmd; echo -e "${BLU}>>${NC} chdir to $my instead of $re"

    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}cd"; echo -n " $cmd "; echo -e "${BLU}>>${NC} [$my | $re]"
        result_cd_test=$((result_cd_test+=1))

    fi
}

function test_cd_wrong_input {
    total_cd_test=$((total_cd_test+=1))
    local cmd=$(echo $1)

    local my=$(echo -e "cd $1\n pwd" | ../mysh 2>&1> /dev/null)
    local re=$(echo -e "cd $1\n pwd" | tcsh 2>&1> /dev/null)

    if [ "$my" != "$re" ]; then
        echo -ne "${RED}[FAILURE]${NC}${BLU}: \
${NC}cd"; echo -n $cmd; echo -e "${BLU}>>${NC} \"$my\" instead of \"$re\""

    else
        echo -ne "${GRN}[SUCESS]${BLU}: \
${NC}cd"; echo -n " $cmd "; echo -e "${BLU}>>${NC} [$my | $re]"
        result_cd_test=$((result_cd_test+=1))

    fi
}

function tests_cd {
    echo -e "-------------------------------------------------"
    echo -e " [START OF ${CYAN}cd${NC} TESTS]"
    echo -e "-------------------------------------------------"
    echo -e "${UL}Tests for correct inputs PWD${NC}"
        test_cd_correct_input ".."
        test_cd_correct_input ""
        test_cd_correct_input ".. \n cd -"
        test_cd_correct_input "/usr"
        test_cd_correct_input "$(HOME)"
        test_cd_correct_input "/"
        test_cd_correct_input "; cd"
        test_cd_correct_input ";;;;;;;;;;;;; cd"
    echo -e "${UL}Tests for wrong inputs${NC}"
        test_cd_wrong_input "azerjksljq"
        test_cd_wrong_input ".. aer"
        test_cd_wrong_input ".. .."
        test_cd_wrong_input "./crash/plus/noway"
        test_cd_wrong_input "./crash/plus/divbyzero"
        test_cd_wrong_input "./crash/divbyzero"
    echo -e "-------------------------------------------------"
    echo -e " [END OF ${CYAN}cd${NC} TESTS: \
${BLU}[$result_cd_test / $total_cd_test]${NC} test(s) passed]"
    echo -e "-------------------------------------------------"
}
