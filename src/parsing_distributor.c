/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_distributor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:47:47 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/22 19:03:36 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	all_heredocs(t_shell *shell)
{
	t_token	*token;
	pid_t	pid;
	int		i;
	// int		status;

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
				g_signal = zombie_prevention_protocol(pid);
				if (g_signal)
				{
					close (token->heredoc_pipe[0]);
					token->heredoc_pipe[0] = -1;
					return (shell->last_errno);
				}
				// waitpid(pid, &status, 0);
				// if (WIFEXITED(status))
				// 	return (WEXITSTATUS(status));
				// if (WIFSIGNALED(status))
				// {
				// 	write(STDERR_FILENO, "boiohboi\n", 10);
				// 	return (WTERMSIG(status));
				// }
			}
			i++;
		}
		token = token->next;
	}
	return (shell->last_errno);
}

// Returns: false when reprompt is needed (e.g. on syntax error)
bool	parsing_distributor(t_shell *shell)
{
	parse_pre(shell, shell->line);
	// if (shell->print_info)// TEST
	// 	TEST_print_elem_list(shell, C_TEAL, true, "Line Element firstcheck");// TEST
	if (shell->line_element_head == NULL)
		return (false);
	tokenize(shell);
	parse_post(shell);
	// sig_heredoc_parent();
	g_signal = 0;
	all_heredocs(shell);
	if (g_signal)
		return (false);
	// sig_parent();
	return (true);
}
