#include "../minishell.h"

int	syntax_token_check(t_shell *shell)
{
	t_token	*current;

	current = shell->token_head;
	while (current != NULL)
	{
		
		current = current->next;
	}
	return (SUCCESS);
}
