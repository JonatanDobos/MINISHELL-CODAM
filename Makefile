NAME	=	minishell

CC		=	cc -g

# CFLAGS=		-Wall -Wextra -Werror

# Adding platform-specific settings for macOS and Ubuntu
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	INCLUDES=	-I /usr/local/opt/readline/include -I ./include
	LDFLAGS=	-L /usr/local/opt/readline/lib -lreadline
else ifeq ($(UNAME_S), Linux)
	INCLUDES=	-I /usr/include/readline -I ./include
	LDFLAGS=	-lreadline
endif

LFTDIR	=	./libft
LIBFT	=	$(LFTDIR)/libft.a

# SRCDIR	=	./test_env_src
# SRC	=	$(SRCDIR)/main.c

SRCDIR	=	./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/envp_export_unset.c \
			$(SRCDIR)/envp_init.c \
			$(SRCDIR)/parsing_distributor.c \
			$(SRCDIR)/tokenizer.c \
			$(SRCDIR)/utils_cmd_list.c \
			$(SRCDIR)/utils_exit.c \
			$(SRCDIR)/utils_free.c \
			$(SRCDIR)/utils_sig_arg_list.c \
			$(SRCDIR)/utils_string.c \
			$(SRCDIR)/utils_syntax.c \

OBJ	=	$(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C $(LFTDIR) all -s

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -f $(OBJ)
	make -C $(LFTDIR) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(LFTDIR)/libft.a

re: fclean all

.PHONY: all clean fclean re
