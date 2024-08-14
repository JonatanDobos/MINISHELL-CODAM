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

# define PROMPT		"\033[0;33mminishell \033[0;31m> \033[0m"

// Colors

# define C_RESET	"\033[0m"
# define C_YELLOW	"\033[0;33m"
# define C_RED		"\033[0;31m"

// Typedefs

typedef unsigned int	t_uint;

// ? env_var niet als token gebruiken, maar de literal string in een node achter cmd head "export" of "unset"
enum	e_token_type
{
	T_SYS_CMD = 0,
	T_BUILTIN,
	T_PIPE,
	T_REDIRECT
};

// LIST

typedef struct s_token
{
	char		**cmd_array;
	char		**redirect;
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
	short		last_errno;
	bool		print_info;// TEST
}	t_shell;

// Colors TESTING:

#define C_DIM		"\033[2m"
#define C_ITALIC	"\033[3m"

#define C_DIM_RED	"\033[2;31m"
#define C_DIM_PURP	"\033[2;35m"
#define C_DIM_TEAL	"\033[2;36m"
#define C_DIM_GREEN	"\033[2;32m"
#define C_B_WHITE	"\033[1;37m"

#define C_BG_BLACK	"\033[40m"
#define C_BG_RED	"\033[41m"
#define C_BG_GREEN	"\033[42m"
#define C_BG_YELLOW	"\033[43m"
#define C_BG_BLUE	"\033[44m"
#define C_BG_PURPLE	"\033[45m"
#define C_BG_CYAN	"\033[46m"
#define C_BG_WHITE	"\033[47m"

#define C_TEAL		"\033[0;36m"
#define C_BLACK		"\033[0;30m"
#define C_GREEN		"\033[0;32m"
#define C_BLUE		"\033[0;34m"
#define C_PURPLE	"\033[0;35m"
#define C_WHITE		"\033[0;37m"

#endif
