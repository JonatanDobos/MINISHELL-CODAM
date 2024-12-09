/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:47:32 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/25 20:18:09 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(int num, const char *message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (message)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (num == 127)
		ft_putstr_fd("command not found", STDERR_FILENO);
	else
		ft_putstr_fd(strerror(num), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	clean_lists(t_shell *shell)
{
	token_clear(&shell->token_head);
	ft_free_null(&shell->line);
	shell->token_head = NULL;
	shell->line_element_head = NULL;
}

// attempts to free everything known to shell, then exits
void	exit_clean(t_shell *shell, int num, const char *message)
{
	int	exit_code;

	exit_code = errno;
	if (num != SUCCESS)
	{
		if (message)
			syntax_error(num, message);
		exit_code = num;
	}
	clean_lists(shell);
	ft_free_array(shell->heredoc);
	ft_free_array(shell->envp);
	ft_free_array(shell->envp_sorted);
	ft_free_null(&shell->history);
	rl_clear_history();
	if (errno != SUCCESS)
		exit_code = errno;
	exit(exit_code);
}
