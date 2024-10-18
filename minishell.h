#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "mini_def.h"

// INIT / PARSING
// envp_init.c
char		**create_envp(char **envp);

// envp_sorting.c
void		sort_envp(char **array);
char		**create_envp_sorted(char **envp);
int			export_envar_to_sorted_array(char *envar, char ***envp);

// syntax_pre.c
bool		syntax_pre(const char *line);

// parsing_distributor.c
bool		parsing_distributor(t_shell *d);

// parsing_pretokenize.c
void		parse_pre(t_shell *shell, char *line);

// parsing_posttokenize.c
void		parse_post(t_shell *shell);
void		format_element_str(t_shell *shell, char **cmd);
void		delete_quotes(char *str);

// parse_expandable.c
char		*parse_envp(char **envp, char *str, size_t i);
char		*expand_env_in_str(t_shell *shell, char *str);
char		*insert_envp_in_str(t_shell *shell, char *str, size_t i);

//tokenize.c
int			tokenize(t_shell *shell);

// EXECUTION
// pipe_execution.c
int			execute_builtin(t_shell *shell, char **cmd_array, char ***envp);
void		execute_sys_cmd(char **cmd_array, char **envp);

// pipe_forking_redirection.c
int			execution(t_shell *shell);

// BUILTINS
// builtin_pwd_cd_env_echo_exit.c
int			builtin_cd(char **cmd_array, char ***envp, char ***envp_sorted);
int			builtin_pwd(char **envp);
int			builtin_env(char **envp);
int			builtin_echo(char **cmd_array, char **envp);
int			builtin_exit(t_shell *shell, char **cmd_array, char **envp);

// builtin_unset_export.c
int			builtin_unset(char *envar, char **envp);
int			builtin_export(char *envar, char ***envp, char ***sorted);

// builtin_heredoc.c
void		builtin_heredoc(t_shell *shell, char *delim, char *heredoc);

// exit_clean.c
void		syntax_error(int num, char *message);
void		exit_clean(t_shell *shell, int num, char *message);
// void	exit_va_free(t_shell *d, int num, char *message, int amount, ...);

// UTILS
// utils_builtin.c
int			export_syntax(const char *envar);
int			unset_syntax(const char *envar);
char		*get_env(char **envp, const char *key);
int			print_export_list(char **envp);

// utils_error_print.c
void		export_error(char *envar);
void		unset_error(char *envar);

// utils_envp_sort.c
bool		export_sorted_syntax(char *envar);
void		ptr_switch(char **src_index, char **dest_index);
char		*strdup_export_format(const char *str);
short		cmp_export_sort(char *relevant, char *compared_to);
int			envp_key_index(char **envp, char *key);

// utils_string.c
char		*strdup_index(char *str, size_t	start, size_t end);
char		*ft_onlyspace(char *str);
char		*str_insert(char *str, char *insert, size_t start, size_t len_del);
void		str_pre_format(char *str);

// utils_free.c
void		free_va(int amount, ...);
void		clean_lists(t_shell *shell);

// utils_mod_gnl.c
char		*get_next_line_heredoc(int fd);

// utils_open_redir_files.c
void		open_files(t_shell *shell, t_token *token);
bool		check_for_heredoc(char **redir);

// utils_parsing.c
bool		istoken(char c);
size_t		skip_redir_ws(char *line);
size_t		skip_to_next_quote(const char *line, size_t i);
size_t		skip_to_end_quote(const char *line, size_t i);

// utils_token_list.c
void		token_add_back(t_token **node, t_token *new);
t_token		*token_last(t_token *node);
t_token		*token_new(char **cmd_array, char **redirect, short type);
void		token_clear(t_token **node);
void		token_delone(t_token *node);

// utils_fd_manipulate.c
void		set_input(t_shell *shell, int input_fd);
void		set_output(t_shell *shell, int output_fd);
void		set_infile(t_shell *shell, char *infile);
void		set_outfile_append(t_shell *shell, char *outfile);
void		set_outfile_trunc(t_shell *shell, char *outfile);

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