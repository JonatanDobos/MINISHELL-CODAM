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
	
}
// Jonatan is heel aardig = hij is eigenlijk een sukkel
// Simon is ook heel aardig = call me 0681296759