NAME	=	libft.a

CFLAGS	=	-Wall -Wextra -Werror

SRC		=	ft_abs.c \
			ft_arrdup.c \
			ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_cpy.c \
			ft_free_null.c \
			ft_free_array.c \
			ft_intlen_base.c \
			ft_intlen.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_memchr.c \
			ft_memclear.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_printf.c \
			ft_putchar_fd.c \
			ft_putchar.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putnbr_base.c \
			ft_putnbr.c \
			ft_putpointer.c \
			ft_putstr_fd.c \
			ft_putstr.c \
			ft_realloc_array.c \
			ft_sign.c \
			ft_split.c \
			ft_str_toupper.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strchr_null.c \
			ft_strdup.c \
			ft_strdup_d.c \
			ft_striteri.c \
			ft_strjoin_d.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strlen_null.c \
			ft_strmapi.c \
			ft_strnarr.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_swap_ints.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_writing.c \
			ft_cpy.c \
			get_next_line.c \

OBJ		=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
