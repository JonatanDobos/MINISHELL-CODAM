/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 18:47:36 by svan-hoo      #+#    #+#                 */
/*   Updated: 2024/12/05 16:53:43 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

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

static void	read_loop(t_shell *shell, t_term original_termios)
{
	while (true)
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &original_termios) != 0)
			exit_clean(shell, errno, "tcsetattr() failed\n");
		sig_interactive();
		shell->line = readline(PROMPT);
		sig_parent();
		if (shell->line == NULL)
			exit_clean(shell, errno, NULL);
		line_history_management(shell);
		if (syntax_pre(shell, shell->line) == false)
			continue ;
		if (g_signal)
			shell->last_errno = g_signal;
		g_signal = 0;
		if (parsing_distributor(shell) && !g_signal)
		{
			shell->last_errno = execution(shell);
			if (shell->last_errno == ENOMEM)
				exit_clean(shell, errno, "malloc fail");
		}
		clean_lists(shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_term	original_termios;

	init_shell(&shell, argc, argv, envp);
	g_signal = 0;
	if (tcgetattr(STDIN_FILENO, &original_termios) != 0)
		exit_clean(&shell, errno, "tcgetattr() failed\n");
	read_loop(&shell, original_termios);
	return (shell.last_errno);
}
