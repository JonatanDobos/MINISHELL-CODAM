#include "../minishell.h"

// PARSING:

void	check_for_exit(t_shell *shell)
{
	if (ft_strncmp(shell->line, "exit", 5) == SUCCESS)
		exit_clean(shell, SUCCESS, NULL);
}

// Returns: false when reprompt is needed (e.g. on syntax error)
bool	parsing_distributor(t_shell *shell)
{
	check_for_exit(shell);
	if (!parse_line_to_elem(shell))
		return (false);
	if (shell->print_info)// TEST
		TEST_print_elem_list(shell, C_TEAL, true, "Line Element firstcheck");// TEST
	tokenize(shell);
	return (true);
}
