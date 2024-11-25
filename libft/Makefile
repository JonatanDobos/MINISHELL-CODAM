NAME	=	libft.a

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

SRCDIR	=	./src
SRC		=	$(SRCDIR)/ft_abs.c \
			$(SRCDIR)/ft_array_append.c \
			$(SRCDIR)/ft_array_index_ins.c \
			$(SRCDIR)/ft_array_size.c \
			$(SRCDIR)/ft_arrdup.c \
			$(SRCDIR)/ft_atoi.c \
			$(SRCDIR)/ft_bzero.c \
			$(SRCDIR)/ft_calloc.c \
			$(SRCDIR)/ft_cpy.c \
			$(SRCDIR)/ft_free_null.c \
			$(SRCDIR)/ft_free_array.c \
			$(SRCDIR)/ft_intlen_base.c \
			$(SRCDIR)/ft_intlen.c \
			$(SRCDIR)/ft_isalnum.c \
			$(SRCDIR)/ft_isupper.c \
			$(SRCDIR)/ft_islower.c \
			$(SRCDIR)/ft_isalpha.c \
			$(SRCDIR)/ft_isascii.c \
			$(SRCDIR)/ft_isdigit.c \
			$(SRCDIR)/ft_isprint.c \
			$(SRCDIR)/ft_iswhitespace.c \
			$(SRCDIR)/ft_itoa.c \
			$(SRCDIR)/ft_lstadd_back.c \
			$(SRCDIR)/ft_lstadd_front.c \
			$(SRCDIR)/ft_lstclear.c \
			$(SRCDIR)/ft_lstdelone.c \
			$(SRCDIR)/ft_lstiter.c \
			$(SRCDIR)/ft_lstlast.c \
			$(SRCDIR)/ft_lstmap.c \
			$(SRCDIR)/ft_lstnew.c \
			$(SRCDIR)/ft_lstsize.c \
			$(SRCDIR)/ft_memchr.c \
			$(SRCDIR)/ft_memclear.c \
			$(SRCDIR)/ft_memcmp.c \
			$(SRCDIR)/ft_memcpy.c \
			$(SRCDIR)/ft_memmove.c \
			$(SRCDIR)/ft_memset.c \
			$(SRCDIR)/ft_printf.c \
			$(SRCDIR)/ft_putarray.c \
			$(SRCDIR)/ft_putchar_fd.c \
			$(SRCDIR)/ft_putchar.c \
			$(SRCDIR)/ft_putendl_fd.c \
			$(SRCDIR)/ft_putnbr_fd.c \
			$(SRCDIR)/ft_putnbr_base.c \
			$(SRCDIR)/ft_putnbr.c \
			$(SRCDIR)/ft_putpointer.c \
			$(SRCDIR)/ft_putstr_fd.c \
			$(SRCDIR)/ft_putstr.c \
			$(SRCDIR)/ft_realloc_array.c \
			$(SRCDIR)/ft_sign.c \
			$(SRCDIR)/ft_split.c \
			$(SRCDIR)/ft_str_toupper.c \
			$(SRCDIR)/ft_strcat.c \
			$(SRCDIR)/ft_strchr.c \
			$(SRCDIR)/ft_strchr_null.c \
			$(SRCDIR)/ft_strdup.c \
			$(SRCDIR)/ft_strdup_d.c \
			$(SRCDIR)/ft_stris.c \
			$(SRCDIR)/ft_striteri.c \
			$(SRCDIR)/ft_strjoin_d.c \
			$(SRCDIR)/ft_strjoin.c \
			$(SRCDIR)/ft_strlcat.c \
			$(SRCDIR)/ft_strlcpy.c \
			$(SRCDIR)/ft_strlen.c \
			$(SRCDIR)/ft_strlen_null.c \
			$(SRCDIR)/ft_strmapi.c \
			$(SRCDIR)/ft_strnarr.c \
			$(SRCDIR)/ft_strncmp.c \
			$(SRCDIR)/ft_strnstr.c \
			$(SRCDIR)/ft_strrchr.c \
			$(SRCDIR)/ft_strtrim.c \
			$(SRCDIR)/ft_substr.c \
			$(SRCDIR)/ft_swap_ints.c \
			$(SRCDIR)/ft_swap.c \
			$(SRCDIR)/ft_tolower.c \
			$(SRCDIR)/ft_toupper.c \
			$(SRCDIR)/ft_writing.c \
			$(SRCDIR)/ft_cpy.c \
			$(SRCDIR)/get_next_line.c \

OBJDIR	=	./obj
OBJ		=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -f $(OBJ)
	rm -df $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
