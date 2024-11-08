/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:47:34 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 23:12:14 by svan-hoo         ###   ########.fr       */
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

static void	run_heredoc(t_shell *shell, t_token *token, char *delimiter)
{
	char	*line;
	int		d_len;

	rl_clear_history();
	d_len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			exit_clean(shell, errno, "run_heredoc() readline()");
		if (!ft_strncmp(line, delimiter, d_len + 1))
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

static pid_t	set_heredoc(t_shell *shell, t_token *token, char *delimiter)
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

int	all_heredocs(t_shell *shell)
{
	t_token	*token;
	pid_t	pid;
	int		i;

	token = shell->token_head;
	while (token)
	{
		i = 0;
		while (token->redirect && token->redirect[i])
		{
			if (!ft_strncmp(token->redirect[i], "<<", 2))
			{
				pid = set_heredoc(shell, token,
						token->redirect[i] + skip_redir_ws(token->redirect[i]));
				if (pid == -1)
					exit_clean(shell, errno, "all_heredocs() fork()");
				shell->last_errno = zombie_prevention_protocol(pid);
			}
			i++;
		}
		token = token->next;
	}
	return (shell->last_errno);
}
