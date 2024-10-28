/*
MINISHELL:

	Part list:
	- History management
	- Cmd management
	- File/ dir management
	- Sig management
*/

#include "../minishell.h"

void	TEST_printline(t_shell *shell);// TEST

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
		sig_noninteractive();
		if (shell->line == NULL)
			exit_clean(shell, errno, NULL);
		line_history_management(shell);
		if (syntax_pre(shell->line) == false)
		{
			ft_putstr_fd("minishell: Function not implemented\n", STDERR_FILENO);
			continue ;
		}
		// TEST
		TEST_printline(shell);
		// TEST
		if (parsing_distributor(shell))// if return = false: reprompt
		{
			// TEST
			if (shell->print_info)
			{
				TEST_print_token_lst(shell, C_GREEN, true, "Token");
				TEST_print_elem_list(shell, C_RED, true, "Line Element lastcheck");
				// TEST_print_pointer_arr(shell->envp, ">", C_BG_PURPLE, true, C_BG_YELLOW, "envp");
			}
			// TEST
			shell->last_errno = execution(shell);// experimental?
			if (shell->last_errno == ENOMEM)
				exit_clean(shell, errno, "malloc fail");
		}
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
