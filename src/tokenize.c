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

// don't make a new token for each element, nor for each recognized type
// only make a new token when redirect or PIPE is found
// e.g. "echo ls -a" should be 1 token (T_BUILTIN) with 3 cmd_array elements
int	tokenize(t_shell *shell)
{
	t_list	*current;
	t_token	*new_token;
	short	type;

	current = shell->line_element_head;
	while (current)
	{
		type = token_type(current->content);
		if (type == T_BUILTIN || type == T_PIPE || type == T_REDIRECT)
		{
			new_token = token_new(NULL, type);
			if (new_token == NULL)
				return (EXIT_FAILURE);
			token_add_back(&shell->token_head, new_token);
		}
		ft_array_append(token_last(shell->token_head)->cmd_array, current->content);
		current = current->next;
	}
	// free line_element_head
	return (SUCCESS);
}

// int	tokenize(t_shell *shell)
// {
// 	t_list	*current;
// 	t_token	*new_token;
// 	short	type;

// 	current = shell->line_element_head;
// 	while (current)
// 	{
// 		type = token_type(current->content);
// 		while (type == T_PIPE)
// 		{
// 			current = current->next;
// 			type = token_type(current->content);
// 		}
// 		if (type == T_REDIRECT)
// 		{
// 			new_token = token_new(NULL, type);
// 			if (new_token == NULL)
// 				return (EXIT_FAILURE);
// 			token_add_back(&shell->token_head, new_token);
// 		}
// 		ft_array_append(token_last(shell->token_head)->cmd_array, current->content);
// 		current = current->next;
// 	}
// 	// free line_element_head
// 	return (SUCCESS);
// }
