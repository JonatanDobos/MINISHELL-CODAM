/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_distributor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:47:47 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/14 19:38:31 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	all_heredocs(t_shell *shell)
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
				if (shell->last_errno)
					return (shell->last_errno);
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
	sig_heredoc_parent();
	all_heredocs(shell);
	sig_parent();
	return (true);
}
