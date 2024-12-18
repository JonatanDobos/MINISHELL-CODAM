/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 18:47:34 by svan-hoo      #+#    #+#                 */
/*   Updated: 2024/12/18 15:41:02 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	endoffile_warning(
		const char *line, const char *delimiter, int i)
{
	if (line == NULL)
	{
		ft_putstr_fd("minishell: warning: here-document at line ",
			STDERR_FILENO);
		ft_putnbr_fd(i,
			STDERR_FILENO);
		ft_putstr_fd(" delimited by end-of-file (wanted `",
			STDERR_FILENO);
		ft_putstr_fd(delimiter,
			STDERR_FILENO);
		ft_putstr_fd("')\n",
			STDERR_FILENO);
	}
}

static void	run_heredoc(t_shell *shell, t_token *token, char *delimiter)
{
	char	*line;
	int		i;

	i = 0;
	rl_clear_history();
	while (1)
	{
		line = readline("> ");
		endoffile_warning(line, delimiter, ++i);
		if (line == NULL)
			exit_clean(shell, errno, "run_heredoc() readline()");
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		line = expand_env_in_str(shell, line);
		if (line == NULL)
			exit_clean(shell, 0, "run_heredoc() expand_env_in_str()");
		ft_putendl_fd(line, token->heredoc_pipe[1]);
		ft_free_null(&line);
	}
	ft_free_null(&line);
}

// take out perror to save lines: if close(fd) != -1, fd = -1;
pid_t	set_heredoc(t_shell *shell, t_token *token, char *delimiter)
{
	pid_t	pid;

	if (token->heredoc_pipe[0] != -1 && close(token->heredoc_pipe[0]) != -1)
		token->heredoc_pipe[0] = -1;
	if (token->heredoc_pipe[1] != -1 && close(token->heredoc_pipe[1]) != -1)
		token->heredoc_pipe[1] = -1;
	if (pipe(token->heredoc_pipe) == -1)
		exit_clean(shell, errno, "set_heredoc() pipe()");
	sig_heredoc_parent();
	pid = fork();
	if (pid == 0)
	{
		sig_child();
		if (close(token->heredoc_pipe[0]) == -1)
			perror("token->heredoc_pipe[0]");
		token->heredoc_pipe[0] = -1;
		run_heredoc(shell, token, delimiter);
		if (close(token->heredoc_pipe[1]) == -1)
			perror("token->heredoc_pipe[1]");
		token->heredoc_pipe[1] = -1;
		exit_clean(shell, errno, "set_heredoc() child");
	}
	if (close(token->heredoc_pipe[1]) != -1)
		token->heredoc_pipe[1] = -1;
	return (pid);
}
