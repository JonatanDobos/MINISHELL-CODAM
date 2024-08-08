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
SRC		=	$(SRCDIR)/_TEST.c\
			$(SRCDIR)/main.c \
			$(SRCDIR)/builtin_export_unset.c \
			$(SRCDIR)/builtin_pwd_cd_env_echo.c \
			$(SRCDIR)/envp_init.c \
			$(SRCDIR)/parse_expandable.c \
			$(SRCDIR)/parsing_distributor.c \
			$(SRCDIR)/parsing.c \
			$(SRCDIR)/tokenize.c \
			$(SRCDIR)/execution.c \
			$(SRCDIR)/utils_builtin.c \
			$(SRCDIR)/utils_exit.c \
			$(SRCDIR)/utils_fd_manipulate.c \
			$(SRCDIR)/utils_free.c \
			$(SRCDIR)/utils_string.c \
			$(SRCDIR)/utils_token_list.c

OBJ	=	$(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C $(LFTDIR) all -s

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C $(LFTDIR) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(LFTDIR)/libft.a

re: fclean all

.PHONY: all clean fclean re
