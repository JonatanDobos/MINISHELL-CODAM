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

# define C_RESET	"\033[0m"
# define C_YELLOW	"\033[0;33m"
# define C_RED		"\033[0;31m"

// TESTING Colors (_TEST.c)

# define C_DIM		"\033[2m"
# define C_ITALIC	"\033[3m"

# define C_DIM_RED	"\033[1;31m"

# define C_TEAL		"\033[0;36m"
# define C_BLACK	"\033[0;30m"
# define C_GREEN	"\033[0;32m"
# define C_BLUE		"\033[0;34m"
# define C_PURPLE	"\033[0;35m"
# define C_WHITE	"\033[0;37m"


// Typedefs

typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;

// ? env_var niet als token gebruiken, maar de literal string in een node achter cmd head "export" of "unset"
enum	e_tokens
{
	T_NO_ACTION = 0,
	T_BUILTIN,
	T_PIPE,
	T_REDIRECT,
	T_FILE,
};

// LIST

typedef struct s_token
{
	t_list		*element_head;
	char		**cmd_array;
	short		type;
	void		*next;
}	t_token;

// STRUCTS

typedef struct s_shell
{
	t_token		*token_head;
	t_list		*line_element_head;
	char		*history;
	char		*line;
	char		**envp;
	bool		print_info;// TEST
}	t_shell;

#endif
