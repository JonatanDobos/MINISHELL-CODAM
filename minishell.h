#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "mini_def.h"

// Function parameters

// parsing.c

void		parsing_distributor(t_shell *d);

// envp_parse.c

size_t		parse_envp(t_shell *shell, size_t i);

// envp_init.c

char		**create_envp(char **envp);

// utils_syntax.c

bool		syntax_check(const char *line);

// utils_string.c

char		*strdup_index(char *str, size_t	start, size_t end);

// utils_exit.c

void		exit_clean(t_shell *shell, int num, char *message);
// void	exit_va_free(t_shell *d, int num, char *message, int amount, ...);

// utils_freeing.c

void		free_setnull(void **ptr);
void		free_va(int amount, ...);

// utils_sig_arg_list.c

void		sig_arg_add_back(t_token **node, t_token *new);
t_token		*sig_arg_last(t_token *node);
t_token		*sig_arg_new(t_list **element_head, char **cmd_array, short token);
void		sig_arg_clear(t_token **node);
void		sig_arg_delone(t_token *node);

// _TEST.c

void		TEST_print_token_lst(t_token **head);
void		TEST_print_string_lst(t_list **head);
void		TEST_print_pointer_arr(char **arr);

#endif
