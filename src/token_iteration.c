#include "../minishell.h"

//move to header
typedef t_tokenfunc

int	token_iteration(t_shell *shell, t_tokenfunc)
{
	t_token	*current;

	current = shell->token_head;
	while (current != NULL)
	{
		
		current = current->next;
	}
	return (SUCCESS);
}
