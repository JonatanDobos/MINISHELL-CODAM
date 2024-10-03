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


SRCDIR	=	./src
SRC		=	$(SRCDIR)/_TEST.c\
			$(SRCDIR)/main.c \
			$(SRCDIR)/builtin_unset_export.c \
			$(SRCDIR)/builtin_cd.c \
			$(SRCDIR)/builtin_pwd_env_echo.c \
			$(SRCDIR)/envp_init.c \
			$(SRCDIR)/parse_expandable.c \
			$(SRCDIR)/parsing_distributor.c \
			$(SRCDIR)/parsing_posttokenize.c \
			$(SRCDIR)/parsing_pretokenize.c \
			$(SRCDIR)/pipe_execution.c \
			$(SRCDIR)/pipe_forking.c \
			$(SRCDIR)/signals.c \
			$(SRCDIR)/syntax_pre.c \
			$(SRCDIR)/tokenize.c \
			$(SRCDIR)/utils_builtin.c \
			$(SRCDIR)/utils_exit.c \
			$(SRCDIR)/utils_fd_manipulate.c \
			$(SRCDIR)/utils_free.c \
			$(SRCDIR)/utils_parsing.c \
			$(SRCDIR)/utils_string.c \
			$(SRCDIR)/utils_token_list.c

OBJDIR	=	./obj
OBJ		=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all:  $(NAME)

$(LIBFT):
	make -C $(LFTDIR) all -s

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)
	rm -df $(OBJDIR)
	make -C $(LFTDIR) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(LFTDIR)/libft.a

re: fclean all

.PHONY: all clean fclean re
