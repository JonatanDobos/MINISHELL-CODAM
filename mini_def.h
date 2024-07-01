#ifndef MINI_DEF_H
# define MINI_DEF_H

// Colors

# define C_RESET "\033[0m"
# define C_TEAL "\033[0;36m"
# define C_YELLOW "\033[0;33m"
# define C_RED "\033[31;1m"

// Typedefs

typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;

// ? env_var niet als token gebruiken, maar de literal string in een node achter cmd head "export" of "unset"
enum	e_tokens
{
	T_NO_ACTION,
	T_BUILTIN,
	T_PIPE,
	T_REDIRECT,
	T_FILE
};

// STRUCTS

// LISTS

typedef struct s_generic_string_node
{
	char	*data;
	void	*next;
}	t_string_node;

// generic node types
typedef t_string_node	t_list;

typedef struct s_significant_argument
{
	t_list		**cmd_head; // can be used as single pointer, head stored in sig_argument node only
	char		**cmd_array;
	short		token;
	void		*next;
}	t_sig_arg;

typedef struct s_shell
{
	t_sig_arg	**sig_arg_head;
	char		**history;
	char		*line;
	char		**envp;
}	t_shell;

#endif
