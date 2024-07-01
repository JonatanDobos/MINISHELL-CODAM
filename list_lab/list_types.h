#ifndef LIST_TYPES_H
# define LIST_TYPES_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <errno.h>
# include <stdbool.h>

// ENUMS
enum	e_tokens
{
	T_NO_ACTION,
	T_COMMAND,
	T_FILE,
	T_BUILTIN,
	T_PIPE,
	T_REDIRECT,
	T_ENV_VAR
};

// LISTS (node types with their respective getnext functions)
// this part should be in libft, along with other generic types like int
// >
// getnext function type
typedef void	*(*t_getnext_func)(void *node);

typedef struct s_generic_string_node
{
	char	*data;
	void	*next;
}	t_string_node;

t_getnext_func	getnext_string;
// <

// generic node types
typedef t_string_node	t_list;

// special node types
typedef struct s_significant_argument
{
	t_list		**element_head;
	char		**cmd_array;
	short		token;
	void		*next;
}	t_token_node;

t_getnext_func	getnext_token;

// FUNCTIONS
t_string_node	*new_node_string(char *data);
t_token_node	*new_node_sig_arg(t_list **element_head, char **cmd_array, short token);
void			lstadd_back(void **head, t_getnext_func getnext, void *new_node);
void			*lstlast(void **head, t_getnext_func getnext);
void			lstfree(void **head, t_getnext_func getnext);

bool			TEST_print_lst(void **head, t_getnext_func getnext);

#endif