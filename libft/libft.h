/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:53:50 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/27 22:09:58 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>

# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 100
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

enum	e_return
{
	ERROR = -1,
	SUCCESS,
	FAILURE
};

size_t		ft_strlcat(char *dst, const char *src, size_t l);
size_t		ft_strlcpy(char *dst, const char *src, size_t l);
size_t		ft_strlen(const char *c);
int			ft_strlen_null(const char *str);
int			ft_strcat(char *dest, const char *src);
int			ft_intlen(int n);
int			ft_cpy(char *dest, const char *src, int n);

int			ft_atoi(const char *c);
void		ft_bzero(void *src, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_itoa(int n);
void		ft_swap_ints(int *a, int *b);

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

int			ft_str_toupper(char *src);

void		*ft_memchr(const void *src, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		ft_memclear(char *src, size_t n);
void		*ft_memset(void *src, int c, size_t n);

void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *str, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *str, int fd);

int			ft_putnbr(long n);
int			ft_putchar(char c);
int			ft_putpointer(unsigned long p);
int			ft_putstr(char *str);

int			ft_intlen_base(int n, char *base);
int			ft_putnbr_base(long n, char *base);

char		**ft_arrdup(char **arr);
char		**ft_split(const char *str, char c);
char		*ft_strchr(const char *str, int c);
int			ft_strchr_null(const char *str, char c);
char		*ft_strdup(const char *str);
char		*ft_strdup_d(const char *str, const char delim);
void		ft_striteri(char *str, void (*f)(unsigned int, char*));
char		*ft_strjoin_d(const char *s1, const char *s2, const char delim);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_substr(const char *str, unsigned int start, size_t len);
char		*ft_strmapi(const char *str, char (*f)(unsigned int, char));

void		*ft_free_null(char **pp);
void		ft_free_array(char **array);
char		**ft_realloc_array(char **array, size_t size);

int			ft_strncmp(const char *a, const char *b, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t n);
char		*ft_strrchr(const char *str, int c);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_strnarr(char **haystack, char *needle, size_t n);

void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);

int			ft_abs(int value);
short		ft_sign(int value);

int			ft_writing(const char *str, int n);

int			ft_printf(const char *form, ...);
char		*get_next_line(int fd);

#endif
