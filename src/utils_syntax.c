#include "../minishell.h"

void	syntax_error(void)
{
		write(STDERR_FILENO, "Syntax Error\n", 14);
}

bool	syntax_export(t_token *token)
{
	char	*envar;
	int		i;

	if (!token
		|| !token->element_head
		|| !token->element_head->next
		|| !token->element_head->next->content)
		return (false);
	envar = token->element_head->next->content;
	i = 0;
	while (envar[i] && envar[i] != '=')
	{
		if (!ft_isalnum(envar[i]) && envar[i] != '_')
			return (false);
		++i;
	}
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
