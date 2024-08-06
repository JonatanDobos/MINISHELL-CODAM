#include "../minishell.h"

bool	syntax_envar(t_token *token)
{
	if (!token
		|| !token->element_head
		|| !token->element_head->next
		|| !token->element_head->next->content)
		return (false);
	return (true);
}
