##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile for minishell lib
##

CC	=	gcc

RMF	=	rm -f

SRC	=	./get_next_line.c	\
		./flag_handling.c	\
		./int_to_str.c		\
		./my_print.c		\
		./tools.c			\
		./tools_2.c			\
		./tools_3.c			\
		./tools_4.c			\
		./tools_5.c			\
		./tools_6.c			\
		./free_array.c

NAME	=	libmy.a

OBJ		=	$(SRC:.c=.o)

all: $(NAME)

$(NAME):
	$(CC) -c $(SRC) -iquote../../include
	ar rc $(NAME) $(OBJ)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)
