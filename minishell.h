#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "mini_def.h"

// Function parameters

//tokenize.c
int			tokenize(t_shell *shell);

// parsing_distributor.c
bool		parsing_distributor(t_shell *d);

// parsing_pretokenize.c
void		parse_pre(t_shell *shell, char *line);

// parsing_posttokenize.c
void		parse_post(t_shell *shell);
void		check_cmd(t_shell *shell, char **cmd);
void		delete_quotes(char *str);

// parse_expandable.c
char		*parse_envp(char **envp, char *str, size_t i);
char		*expand_env_in_str(t_shell *shell, char *str);

// envp_init.c
char		**create_envp(char **envp);

// pipe_execution.c
int			execute_builtin(char **cmd_array, char ***envp);
void		execute_sys_cmd(char **cmd_array, char **envp);
// pipe_forking.c
int			execution(t_shell *shell);

// syntax_pre.c
bool		syntax_pre(const char *line);

// BUILTINS
// builtin_pwd_cd_env_echo.c
void		builtin_cd(char *operand, char ***envp);
void		builtin_pwd(char **envp);
void		builtin_env(char **envp);
void		builtin_echo(char **cmd_array, char **envp);
// builtin_unset_export.c
void		builtin_unset(char **cmd_array, char **envp);
char		**builtin_export(char *envar, char **envp);

// UTILS
// utils_builtin.c
int			export_syntax(const char *envar);
char		*get_env(char **envp, const char *key);

// utils_string.c
char		*strdup_index(char *str, size_t	start, size_t end);
char		*ft_onlyspace(char *str);
char		*str_insert(char *str, char *insert, size_t start, size_t len_del);
void		str_pre_format(char *str);

// utils_exit.c
void		exit_clean(t_shell *shell, int num, char *message);
// void	exit_va_free(t_shell *d, int num, char *message, int amount, ...);

// utils_free.c
void		free_va(int amount, ...);
void		clean_lists(t_shell *shell);

// utils_parsing.c
bool		istoken(char c);
size_t		skip_redir_whitespace(char *line);
size_t		skip_to_next_quote(const char *line, size_t i);
size_t		skip_to_end_quote(const char *line, size_t i);

// utils_token_list.c
void		token_add_back(t_token **node, t_token *new);
t_token		*token_last(t_token *node);
t_token		*token_new(char **cmd_array, char **redirect, short type);
void		token_clear(t_token **node);
void		token_delone(t_token *node);


// utils_fd_manipulate.c
int			set_input(int input_fd);
int			set_output(int output_fd);
int			open_infile(const char *infile);
int			open_outfile(const char *outfile);

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