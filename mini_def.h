/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_def.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 18:48:41 by svan-hoo      #+#    #+#                 */
/*   Updated: 2024/12/05 16:36:38 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <termios.h>
# include "libft/libft.h"

# define PROMPT			"\033[0;33mminishell \033[0;31m> \033[0m"
# define TOKEN_ERR		"minishell: syntax error near unexpected token "

extern int				g_signal;

enum	e_token_type
{
	T_SYS_CMD = 0,
	T_BUILTIN,
	T_PIPE,
	T_REDIRECT
};

typedef struct termios	t_term;

typedef struct s_token
{
	char				**cmd_array;
	char				**redirect;
	int					heredoc_pipe[2];
	short				type;
	void				*next;
}	t_token;

typedef struct s_shell
{
	t_token				*token_head;
	t_list				*line_element_head;
	char				*history;
	char				*line;
	char				**envp;
	char				**envp_sorted;
	char				**heredoc;
	short				last_errno;
}	t_shell;

#endif
