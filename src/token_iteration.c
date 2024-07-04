#include "../minishell.h"

int	token_iteration(t_shell *shell)
{
	t_token	*current;

	current = shell->token_head;
	while (current != NULL)
	{
		
		current = current->next;
	}
	return (SUCCESS);
}
