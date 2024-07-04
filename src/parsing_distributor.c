#include "../minishell.h"

// PARSING:

void	check_for_exit(t_shell *shell)
{
	if (ft_strncmp(shell->line, "exit", 5) == SUCCESS)
		exit_clean(shell, SUCCESS, NULL);
}

void	parsing_distributor(t_shell *shell)
{
	check_for_exit(shell);
	parse_line_to_elem(shell);
}
