#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "mini_def.h"

// Function parameters

//tokenize.c
int			tokenize(t_shell *shell);

// parsing_distributor.c
bool		parsing_distributor(t_shell *d);

// parsing.c
bool		parse_line_to_elem(t_shell *shell);

// expand_parse.c
char		*parse_envp(char **envp, char *str, size_t i);
char		*expand_env_in_str(t_shell *shell, char *str);

// envp_init.c
char		**create_envp(char **envp);

// execition.c
void		execution(t_shell *shell);

// BUILTINS
// builtin_echo.c
void		builtin_echo(t_shell *shell, t_token *token, char *output_file);
// builtin_export_unset.c
void		builtin_export(t_shell *shell, t_token *token);
void		builtin_unset(t_shell *shell, t_token *token);

// syntax_pre.c
bool		syntax_pre(const char *line);

// UTILS
// utils_syntax.c
void		syntax_error(void);
bool		syntax_export(t_token *token);
bool		syntax_unset(t_token *token);

// utils_string.c
char		*strdup_index(char *str, size_t	start, size_t end);
char		*ft_onlyspace(char *str);

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

// utils_fd_manipulate.c
bool		set_input(int input_fd);
bool		set_output(int output_fd);
int			open_inputfile(const char *inputfile);
int			open_outputfile(const char *outputfile);

// _TEST.c
void		TEST_print_token_lst(
			t_shell *shell,
			char *accent_col,
			bool thick_line,
			char *name);
void		TEST_print_elem_list(
			t_shell *shell,
			char *accent_col,
			bool thick_line,
			char *name);
void		TEST_print_t_list(
			t_list **head,
			char *precursor,
			char *pre_col,
			bool background,
			char *accent_col,
			char *list_name);
void		TEST_print_pointer_arr(
			char **arr,
			char *precursor,
			char *pre_col,
			bool background,
			char *accent_col,
			char *name);

#endif
