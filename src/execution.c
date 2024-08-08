#include "../minishell.h"

static void	execute_builtin(t_shell *shell, t_token *token)
{
	if (!token || !token->cmd_array)
		return ;
	if (!ft_strncmp(token->cmd_array[0], "cd", 3))
		builtin_cd(shell, token->cmd_array);
	if (!ft_strncmp(token->cmd_array[0], "pwd", 4))
		builtin_pwd(shell);
	if (!ft_strncmp(token->cmd_array[0], "env", 4))
		builtin_env(shell);
	if (!ft_strncmp(token->cmd_array[0], "echo", 5))
		builtin_echo(shell, token->cmd_array);
	if (!ft_strncmp(token->cmd_array[0], "unset", 6))
		builtin_unset(shell, token->cmd_array);
	if (!ft_strncmp(token->cmd_array[0], "export", 7))
		builtin_export(shell, token->cmd_array);
}

void	execution(t_shell *shell)
{
	t_token	*token;

	token = shell->token_head;
	while (token != NULL)
	{
		if (token->type == T_BUILTIN)
			execute_builtin(shell, token);
		token = token->next;
	}
}
