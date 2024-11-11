/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:47:36 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/11 19:18:29 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

// void	TEST_printline(t_shell *shell);// TEST

// Initializes struct of all structs: t_shell.
void	init_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	shell->token_head = NULL;
	shell->line_element_head = NULL;
	shell->history = NULL;
	shell->line = NULL;
	shell->last_errno = 0;
	shell->heredoc = NULL;
	shell->envp = create_envp(envp);
	if (shell->envp == NULL)
		exit_clean(shell, errno, NULL);
	shell->envp_sorted = create_envp_sorted(envp);
	if (shell->envp_sorted == NULL)
		exit_clean(shell, errno, NULL);
	(void)envp;
}

// Adds current line to history if:
// line_len > 0 && line != previous line.
// Lastly: strdups line to history.
void	line_history_management(t_shell *shell)
{
	const size_t	len = ft_strlen(shell->line);

	if (len && \
	(!shell->history || ft_strncmp(shell->line, shell->history, len + 1)))
	{
		add_history(shell->line);
		free(shell->history);
		shell->history = ft_strdup(shell->line);
		if (!shell->history)
			exit_clean(shell, errno, NULL);
	}
}

void	read_loop(t_shell *shell)
{
	while (true)
	{
		sig_interactive();
		shell->line = readline(PROMPT);
		sig_parent();
		if (shell->line == NULL)
			exit_clean(shell, errno, NULL);
		line_history_management(shell);
		if (syntax_pre(shell->line) == false)
		{
			shell->last_errno = EINVAL;
			continue ;
		}
		if (parsing_distributor(shell) && !g_signal)
		{
			shell->last_errno = execution(shell);
			if (shell->last_errno == ENOMEM)
				exit_clean(shell, errno, "malloc fail");
		}
		g_signal = 0;
		clean_lists(shell);
	}
	free(shell->history);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	init_shell(&shell, argc, argv, envp);
	read_loop(&shell);
	return (shell.last_errno);
}

// TEST FUNCTIONS:
// INP: "info [gets run with additional info]"
void	TEST_printline(t_shell *shell)
{
	char	*tmp_line;

	if (!ft_strncmp(shell->line, "info ", 5))
	{
		shell->print_info = true;
		tmp_line = ft_strdup(shell->line + 5);
		if (!tmp_line)
			exit_clean(shell, errno, NULL);
		free(shell->line);
		shell->line = tmp_line;
	}
	else
		shell->print_info = false;
}
