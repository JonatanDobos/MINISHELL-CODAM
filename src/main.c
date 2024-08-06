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

short	sig = 0;

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
		rl_on_new_line();
		shell->line = readline(C_YELLOW "mini" C_RED " > " C_RESET);
		if (shell->line == NULL)
			exit_clean(shell, errno, NULL);
		if (syntax_pre(shell->line) == FAILURE)
			printf("syntax error\n");
		TEST_printline(shell);// TEST
		line_history_management(shell);
		if (parsing_distributor(shell))// if return = false: reprompt
			execution(shell);// experimental
		if (shell->print_info)// TEST
		{
			TEST_print_token_lst(shell, C_GREEN, true, "Token");
			TEST_print_elem_list(shell, C_RED, true, "Line Element lastcheck");
		}
		clean_lists(shell);
	}
	free(shell->history);
	rl_clear_history();
}

// Contains the readline() loop.
// FOR TESTING: to print the input of readline() input:
// "print [this will be printed]"
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	init_shell(&shell, argc, argv, envp);
	read_loop(&shell);
	return (SUCCESS);
}

// TEST FUNCTIONS:
// INP: "print [gets printed on stdout]"
// INP: "info [gets run with additional info]"
void	TEST_printline(t_shell *shell)
{
	char	*tmp_line;

	if (ft_strlen(shell->line) >= 7 && !ft_strncmp(shell->line, "print ", 6))
		printf("*\n%s\n*\n", shell->line + 6);
	if (ft_strlen(shell->line) >= 6 && !ft_strncmp(shell->line, "info ", 5))
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
