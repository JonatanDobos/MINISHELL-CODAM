#ifndef MINI_DEF_H
# define MINI_DEF_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <termios.h>

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
	T_NO_ACTION = 1,
	T_BUILTIN = 2,
	T_PIPE = 3,
	T_REDIRECT = 4,
	T_FILE = 5
};

// STRUCTS

typedef struct s_shell
{
	t_sig_arg	**sig_arg_head;
	char		*history;
	char		*line;
	char		**envp;
	bool		print_info;// TEST
}	t_shell;

// LISTS

typedef struct s_significant_argument
{
	t_list		**cmd_head; // can be used as single pointer, head stored in sig_argument node only
	char		**cmd_array;
	short		token;
	void		*next;
}	t_sig_arg;

#endif
