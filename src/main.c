/*
MINISHELL:

	Part list:
	- History management
	- Cmd management
	- File/ dir management
	- Sig management
*/

#include "../minishell.h"

void	TEST_printline(char *line);

short	sig = 0;

// Initializes struct of all structs: t_dad.
void	init_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	shell->sig_arg_head = NULL;
	shell->history = NULL;
	shell->line = NULL;
	shell->envp = create_envp(envp);
	if (shell->envp == NULL)
		exit_clean(shell, errno, NULL);
	(void)envp;
}

// Adds current line to history if:
// line_len > 0 && line != previous line.
// Lastly: strdups line to history.
// void	line_history_management(t_shell *shell)
// {
// 	const size_t	len = ft_strlen(shell->line);

// 	if (len && \
// 	(!shell->history || ft_strncmp(shell->line, shell->history, len + 1)))
// 	{
// 		add_history(shell->line);
// 		free(shell->history);
// 		shell->history = ft_strdup(shell->line);
// 		if (!shell->history)
// 			exit_clean(shell, errno, NULL);
// 	}
// }

// Contains the readline() loop.
// FOR TESTING: to print the input of readline() input:
// "print [this will be printed]"
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	init_shell(&shell, argc, argv, envp);
	while (true)
	{
		rl_on_new_line();
		shell.line = readline(C_YELLOW "mini" C_RED " > " C_RESET);
		if (shell.line == NULL)
			exit_clean(&shell, errno, NULL);
		if (syntax_check(shell.line) == FAILURE)
			printf("syntax error\n");
		TEST_printline(shell.line);
		// line_history_management(&shell);
		parsing_distributor(&shell);
		free(shell.line);
	}
	free(shell.history);
	rl_clear_history();
	return (SUCCESS);
}

// TEST FUNCTIONS:
void	TEST_printline(char *line)
{
	if (ft_strlen(line) >= 7 && !ft_strncmp(line, "print ", 6))
		printf("*\n%s\n*\n", line + 6);
}
