##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile for minishell
##

CC			=	gcc

RM			=	rm -f

LIBPATH		=	./lib/my

ALIAS_DIR	=	alias/

HIST_DIR	=	history/

SRC			=	src/main.c						\
				src/launcher.c					\
				src/str_handling.c				\
				src/command.c					\
				src/process.c					\
				src/setenv.c					\
				src/unsetenv.c					\
				src/path_handling.c				\
				src/binary_research.c			\
				src/cd.c						\
				src/redirection.c				\
				src/pipe.c						\
				src/string_parsing.c			\
				src/binary_tree.c				\
				src/sub_functions.c				\
				src/parsing.c					\
				src/redir_error.c				\
				src/pipe_with_builtin.c			\
				src/echo.c						\
				src/where.c						\
				src/which.c						\
				src/local_variables/getvar.c    \
				src/local_variables/init_var.c  \
				src/local_variables/printvar.c 	\
				src/local_variables/setvar.c    \
				src/local_variables/unsetvar.c  \
				src/local_variables/var_cpy.c	\
				src/local_variables/gestion_local.c	\
				src/conditionnal_operator.c

SRCALIAS	=	src/$(ALIAS_DIR)alias.c					\
				src/$(ALIAS_DIR)alias_builtin.c			\
				src/$(ALIAS_DIR)unalias_builtin.c		\
				src/$(ALIAS_DIR)alias_init.c			\
				src/$(ALIAS_DIR)alias_add.c				\
				src/$(ALIAS_DIR)alias_get.c				\
				src/$(ALIAS_DIR)alias_sort.c			\
				src/$(ALIAS_DIR)alias_print.c			\
				src/$(ALIAS_DIR)alias_parsing_utils.c

SRCHIST		=	src/$(HIST_DIR)history.c						\
				src/$(HIST_DIR)history_builtin.c				\
				src/$(HIST_DIR)init_history_default.c			\
				src/$(HIST_DIR)init_history_from_file.c			\
				src/$(HIST_DIR)get_history.c					\
				src/$(HIST_DIR)print_history.c					\
				src/$(HIST_DIR)add_cmd_in_history.c				\
				src/$(HIST_DIR)move_to_last.c					\
				src/$(HIST_DIR)save_history.c					\

SRCEDIT		=	line_editing/auto_complete.c		\
				line_editing/buffer_copy.c			\
				line_editing/clear_term.c			\
				line_editing/escape_sequence.c		\
				line_editing/get_files.c			\
				line_editing/handle_str.c			\
				line_editing/handle_sigint.c		\
				line_editing/handle_termios.c		\
				line_editing/key_actions.c			\
				line_editing/key_arrows.c			\
				line_editing/key_cut.c				\
				line_editing/key_default.c			\
				line_editing/key_delete.c			\
				line_editing/key_goto.c				\
				line_editing/key_help.c				\
				line_editing/key_restore_buffer.c	\
				line_editing/key_suppr.c			\
				line_editing/key_tab.c				\
				line_editing/key_word_cut.c			\
				line_editing/key_word_goto.c		\
				line_editing/print_prompt.c			\
				line_editing/prompt.c				\
				line_editing/reprint_prompt.c		\
				line_editing/user_prompt.c

SRCLEX	=	parsing/arrlen.c								\
			parsing/delete_cmd.c							\
			parsing/get_cmds.c								\
			parsing/get_wcmds.c								\
			parsing/get_word.c								\
			parsing/op.c									\
			parsing/parser_main.c							\
			parsing/preprocess_wcmd.c						\
			parsing/remove_inihibitors.c					\
			parsing/replace_globbings.c						\
			parsing/replace_magic_quotes.c					\
			parsing/replace_main.c							\
			parsing/sep_cmds.c								\
			parsing/skip.c									\
			parsing/replace_alias.c							\
			parsing/append_on_backslash.c					\
			parsing/sep_cond_oprt.c							\
			src/destroy_2d_2allocs.c						\

ALLSRC	=	$(SRCEDIT) $(SRC) $(SRCALIAS) $(SRCHIST) $(SRCLEX)

SRCTEST	=	test/test.c				\
			test/mysh_2_test.c		\
			$(filter-out src/main.c, $(ALLSRC))

OBJ		=	$(ALLSRC:.c=.o)

NAME	=	42sh

NAMELIB	=	libmy.a

CFLAGS	=	-Wall -Wextra

LDLIBS	=	-L$(LIBPATH)

LDFLAGS	=	-lncurses -lmy

CPPFLAGS	=	-I./include/

CRITFLAGS	=	$(CPPFLAGS) $(LDLIBS) $(LDFLAGS) --coverage -lcriterion

all:	$(NAMELIB) $(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDLIBS) $(LDFLAGS)

$(NAMELIB):
	make -C $(LIBPATH)

debug:
	make -C $(LIBPATH)
	$(CC) -o $(NAME) $(ALLSRC) $(LDLIBS) $(LDFLAGS) $(CPPFLAGS) -g3

clean:
	@make clean -C $(LIBPATH)
	@$(RM) *.gc* unit_test $(OBJ)

fclean: clean
	@make fclean -C $(LIBPATH)
	@$(RM) $(NAME)

re:	fclean all

tests_run: $(NAMELIB)
	$(CC) -o unit_test $(SRCTEST) $(CRITFLAGS)
	./unit_test

.PHONY: all clean fclean re tests_run
