#include "../minishell.h"

static void	execute_builtin(t_shell *shell, t_token *token)
{
	if (!token || !token->element_head)
		return ;
	if (!ft_strncmp(token->element_head->content, "echo", 5))
		builtin_echo(shell, token, NULL);
}

void	execution(t_shell *shell)
{
	t_token	*token;

	if (!shell->line_element_head)
		return ;
	token = shell->token_head;
	while (token != NULL)
	{
		if (token->type == T_BUILTIN)
			execute_builtin(shell, token);
		token = token->next;
	}
}
