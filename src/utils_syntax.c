#include "../minishell.h"

bool	syntax_export(t_token *token)
{
	char *envar;

	if (!token
		|| !token->element_head
		|| !token->element_head->next
		|| !token->element_head->next->content)
		return (false);
	envar = token->element_head->next->content;
	if (ft_strchr(envar, '=') <= envar)
		return (false);
	return (true);
}

bool	syntax_unset(t_token *token)
{
	if (!token
		|| !token->element_head
		|| !token->element_head->next
		|| !token->element_head->next->content)
		return (false);
	return (true);
}
