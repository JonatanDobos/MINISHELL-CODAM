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
void		parse_line_to_element(t_shell *shell, char *line);

// parse_expandable.c
char		*parse_envp(char **envp, char *str, size_t i);
char		*expand_env_in_str(t_shell *shell, char *str);

// envp_init.c
char		**create_envp(char **envp);

// pipe_execution.c
void		execute_builtin(char **cmd_array, char **envp);
void		execute_sys_cmd(char **cmd_array, char **envp);
// pipe_forking.c
int			execution(t_shell *shell);

// BUILTINS
// builtin_pwd_cd_env_echo.c
void		builtin_cd(char **cmd_array, char **envp);
void		builtin_pwd(char **envp);
void		builtin_env(char **envp);
void		builtin_echo(char **cmd_array, char **envp);
// builtin_export_unset.c
void		builtin_export(char **cmd_array, char **envp);
void		builtin_unset(char **cmd_array, char **envp);

// UTILS
// utils_syntax.c
void		syntax_error(void);
bool		syntax_export(const char *envar);

// utils_string.c
char		*strdup_index(char *str, size_t	start, size_t end);
char		*ft_onlyspace(char *str);
char		*str_insert(char *str, char *insert, size_t start, size_t len_del);

// utils_exit.c
void		exit_clean(t_shell *shell, int num, char *message);
void		error_exit(int num, char *param);
// void	exit_va_free(t_shell *d, int num, char *message, int amount, ...);

// utils_freeing.c
void		free_va(int amount, ...);
void		clean_lists(t_shell *shell);

// utils_token_list.c
void		token_add_back(t_token **node, t_token *new);
t_token		*token_last(t_token *node);
t_token		*token_new(char **cmd_array, char **redirect, short type);
void		token_clear(t_token **node);
void		token_delone(t_token *node);

// utils_parsing.c
char		*get_env(char **envp, char *key);

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
