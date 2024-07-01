NAME	=	listlab

CC		=	cc

# CFLAGS	=	-Wall -Wextra -Werror

SRC		=	main.c \
			list_general.c \
			list_types.c \
			TEST_print_list.c

OBJ	=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
