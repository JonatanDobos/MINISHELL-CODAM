/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:47:32 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 18:47:33 by svan-hoo         ###   ########.fr       */
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
		ft_putstr_fd("command not found\n", STDERR_FILENO);
	else
		ft_putstr_fd(strerror(num), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
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

// (EXPERIMENTAL)
// Exits the program with exit_clean() after freeing variable amount of pointers
// void	exit_va_free(t_shell *shell, int num, char *message, int amount, ...)
// {
// 	va_list	ptrs_to_free;
// 	int		i;

// 	va_start(ptrs_to_free, amount);
// 	i = 0;
// 	while (i < amount)
// 	{
// 		free_if(va_arg(ptrs_to_free, void *));
// 		++i;
// 	}
// 	va_end(ptrs_to_free);
// 	exit_clean(shell, num, message);
// }
