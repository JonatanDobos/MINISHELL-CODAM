#include "../minishell.h"
// Returns: false when reprompt is needed (e.g. on syntax error)
bool	parsing_distributor(t_shell *shell)
{
	parse_pre(shell, shell->line);
	if (shell->print_info)// TEST
		TEST_print_elem_list(shell, C_TEAL, true, "Line Element firstcheck");// TEST
	if (shell->line_element_head == NULL)
		return (false);
	tokenize(shell);
	parse_post(shell);
	return (true);
}
