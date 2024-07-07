#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "mini_def.h"

// Function parameters

//tokenize.c
int			tokenize(t_shell *shell);

// parsing_distributor.c
void		parsing_distributor(t_shell *d);

// parsing.c
void		parse_line_to_elem(t_shell *shell);

// envp_parse.c
size_t		parse_envp(t_shell *shell, size_t i);

// envp_init.c
char		**create_envp(char **envp);

// UTILS
// utils_syntax.c
bool		syntax_check_line(const char *line);

// utils_string.c
char		*strdup_index(char *str, size_t	start, size_t end);

// utils_exit.c
void		exit_clean(t_shell *shell, int num, char *message);
// void	exit_va_free(t_shell *d, int num, char *message, int amount, ...);

// utils_freeing.c
void		free_va(int amount, ...);
void		clean_lists(t_shell *shell);

// utils_token_list.c
void		token_add_back(t_token **node, t_token *new);
t_token		*token_last(t_token *node);
t_token		*token_new(t_list *element_head, char **cmd_array, short token);
void		token_clear(t_token **node);
void		token_delone(t_token *node);

// utils_parsing.c
bool		ft_iswhitespace(char c);

// _TEST.c
void		TEST_print_token_lst(t_shell *shell, char *accent_col, bool thick_line, char *name);
void		TEST_print_elem_list(t_shell *shell, char *accent_col, bool thick_line, char *name);
void		TEST_print_t_list(
	t_list **head,
	t_uchar *precursor,
	char *pre_col,
	bool background,
	char *accent_col,
	char *list_name);
void		TEST_print_pointer_arr(
	char **arr,
	t_uchar *precursor,
	char *pre_col,
	bool background,
	char *accent_col,
	char *name);

#endif
