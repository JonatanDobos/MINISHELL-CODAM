#include "../minishell.h"

static short	token_type(const char *element)
{
	if (ft_strncmp(element, "cd", 3) == 0
		|| ft_strncmp(element, "pwd", 4) == 0
		|| ft_strncmp(element, "env", 4) == 0
		|| ft_strncmp(element, "echo", 5) == 0
		|| ft_strncmp(element, "unset", 6) == 0
		|| ft_strncmp(element, "export", 7) == 0)
		return (T_BUILTIN);
	if (ft_strncmp(element, ">", 2) == 0
		||ft_strncmp(element, "<", 2) == 0)
		return (T_REDIRECT);
	if (ft_strncmp(element, "|", 2) == 0)
		return (T_PIPE);
	else
		return (T_SYS_CMD);
}

int	tokenize(t_shell *shell)
{
	t_list	*current;
	t_token	*new_token;

	current = shell->line_element_head;
	while (current)
	{
		if (current && token_type(current->content) == T_PIPE)
			current = current->next;
		if (token_type(current->content) == T_PIPE)
			exit_clean(shell, 22, "syntax error near unexpected token '|'");
		new_token = token_new(NULL, token_type(current->content));
		if (new_token == NULL)
			exit_clean(shell, errno, NULL);
		token_add_back(&shell->token_head, new_token);
		while (current && token_type(current->content) != T_PIPE)
		{
			token_last(shell->token_head)->cmd_array = ft_array_append(
				token_last(shell->token_head)->cmd_array, current->content);
			current = current->next;
		}
	}
	// free line_element_head
	return (SUCCESS);
}
