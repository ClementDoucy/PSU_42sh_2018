##
## EPITECH PROJECT, 2019
## PSU_minishell1_2018
## File description:
## test_format
##

source ./utils/colors.sh
result_format_test=
total_format_test=

function test_format {
    total_format_test=$((total_format_test+=1))
    local my=$(echo -e "$1\n pwd" | ../mysh)
    local re=$(echo -e "$1\n pwd" | tcsh)

    if [ "$my" != "$re" ]; then
        echo -e "${RED}[FAILURE]${NC}${BLU}:\
${NC}$1${BLU}>>${NC} chdir to $my instead of $re"

    else
        echo -e "${GRN}[SUCESS]${BLU}:\
${NC}$1${BLU}>>${NC} [$my | $re]"
        result_format_test=$((result_format_test+=1))

    fi
}

function tests_format {
    echo -e "-------------------------------------------------"
    echo -e " [START OF ${CYAN}format${NC} TESTS]"
    echo -e "-------------------------------------------------"
    echo -e "${UL}Tests for spaces${NC}"
        test_format " cd .."
        test_format "cd .. "
        test_format " cd .. "
        test_format "      cd    ..    "
    echo -e "${UL}Tests for tabulations${NC}"
        test_format "\tcd\t.."
        test_format "cd\t..\t"
        test_format "\tcd\t..\t"
        test_format "\t\t\tcd\t\t\t..\t\t\t"
    echo -e "${UL}Tests for tabulations and spaces${NC}"
        test_format "\t  cd   \t.."
        test_format "cd\t   ..  \t"
        test_format "  \t  cd  \t  ..  \t  "
        test_format "\t\t\tcd\t \t \t..\t\t\t"
    echo -e "-------------------------------------------------"
    echo -e " [END OF ${CYAN}format${NC} TESTS: \
${BLU}[$result_format_test / $total_format_test]${NC} test(s) passed]"
    echo -e "-------------------------------------------------"
}
