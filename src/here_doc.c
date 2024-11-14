/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:47:34 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/14 19:39:00 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Expands envp inside string
// *str freed inside function
static char	*insert_env(t_shell *shell, char *str, size_t i)
{
	const char	*check = str;
	size_t		j;

	if (!str)
		return (NULL);
	str = insert_envp_in_str(shell, str, i);
	if (str == check)
	{
		j = i;
		while (!ft_iswhitespace(str[j]))
			++j;
		str = str_insert(str, "", i, j - i);
	}
	return (str);
}

static char	*expand_in_line(t_shell *shell, char *str)
{
	size_t	i;
	bool	double_quote;

	i = 0;
	double_quote = false;
	while (str[i])
	{
		if (str[i] == '\"' && double_quote == true)
			double_quote = false;
		else if (str[i] == '\"' && double_quote == false)
			double_quote = true;
		else if (str[i] == '\'' && double_quote == false)
			i = skip_to_next_quote(str, i);
		else if (str[i] == '$')
		{
			str = insert_env(shell, str, i);
			if (!str)
				return (NULL);
		}
		++i;
	}
	return (str);
}

static void	endoffile_warning(
		const char *line, const char *delimiter, int i)
{
	if (line == NULL)
	{
		ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
		ft_putnbr_fd(i, STDERR_FILENO);
		ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
	}
}

static void	run_heredoc(t_shell *shell, t_token *token, char *delimiter)
{
	char	*line;
	int		i;

	rl_clear_history();
	i = 0;
	while (1)
	{
		line = readline("> ");
		endoffile_warning(line, delimiter, ++i);
		if (line == NULL)
			exit_clean(shell, errno, "run_heredoc() readline()");
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		line = expand_in_line(shell, line);
		if (line == NULL)
			exit_clean(shell, 0, "run_heredoc() expand_in_line()");
		ft_putendl_fd(line, token->heredoc_pipe[1]);
		if (!ft_strncmp(delimiter, "\n", 2))
			break ;
		ft_free_null(&line);
	}
	ft_free_null(&line);
	if (token->heredoc_pipe[1] != -1 && close(token->heredoc_pipe[1]) == -1)
		perror("token->heredoc_pipe[1]");
	token->heredoc_pipe[1] = -1;
}
// take out perror to save lines: if close(fd) != -1, fd = -1;
pid_t	set_heredoc(t_shell *shell, t_token *token, char *delimiter)
{
	pid_t	pid;

	if (token->heredoc_pipe[0] != -1 && close(token->heredoc_pipe[0]) == -1)
		perror("token->heredoc_pipe[0]");
	token->heredoc_pipe[0] = -1;
	if (token->heredoc_pipe[1] != -1 && close(token->heredoc_pipe[1]) == -1)
		perror("token->heredoc_pipe[1]");
	token->heredoc_pipe[1] = -1;
	if (pipe(token->heredoc_pipe) == -1)
		exit_clean(shell, errno, "set_heredoc() pipe()");
	pid = fork();
	if (pid == -1)
		return (pid);
	if (pid == 0)
	{
		sig_heredoc_child();
		if (token->heredoc_pipe[0] != -1 && close(token->heredoc_pipe[0]) == -1)
			perror("token->heredoc_pipe[0]");
		token->heredoc_pipe[0] = -1;
		run_heredoc(shell, token, delimiter);
		exit_clean(shell, errno, "set_heredoc() child");
	}
	if (close(token->heredoc_pipe[1]) == -1)
		exit_clean(shell, errno, "set_heredoc() close()");
	token->heredoc_pipe[1] = -1;
	return (pid);
}
