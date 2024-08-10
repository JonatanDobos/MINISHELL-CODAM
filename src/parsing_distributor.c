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
	parse_line_to_element(shell, shell->line);
	if (shell->print_info)// TEST
		TEST_print_elem_list(shell, C_TEAL, true, "Line Element firstcheck");// TEST
	if (shell->line_element_head == NULL)
		return (false);
	tokenize(shell);
	return (true);
}
