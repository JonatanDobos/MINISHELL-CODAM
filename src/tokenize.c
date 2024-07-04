#include "../minishell.h"

short	token_type(char *element)
{
	if (ft_strncmp(element, "echo", 5) == 0
		|| ft_strncmp(element, "cd", 7) == 0
		|| ft_strncmp(element, "pwd", 7) == 0
		|| ft_strncmp(element, "export", 7) == 0
		|| ft_strncmp(element, "unset", 6) == 0
		|| ft_strncmp(element, "env", 4) == 0)
		return (T_BUILTIN);
	if (ft_strncmp(element, ">", 2) == 0
		||ft_strncmp(element, "<", 2) == 0)
		return (T_REDIRECT);
	if (ft_strncmp(element, "|", 2) == 0)
		return (T_PIPE);
	else
		return (T_NO_ACTION);
}

int	tokenize(t_shell *shell, t_list	**line_element_head)
{
	t_list	*current;
	t_list	*previous;
	t_token	*new_token;
	short	type;

	current = *line_element_head;
	previous = NULL;
	while (current)
	{
		type = token_type(current->content);
		if (type == T_BUILTIN || type == T_PIPE || type == T_REDIRECT)
		{
			new_token = token_new(current, NULL, type);
			if (new_token == NULL)
				return (EXIT_FAILURE);
			token_add_back(&shell->token_head, new_token);
			previous->next = NULL;
		}
		previous = current;
		current = current->next;
	}
	return (SUCCESS);
}
