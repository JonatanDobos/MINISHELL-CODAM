#include "../minishell.h"

static short	get_element_type(const char *element)
{
	if (ft_strncmp(element, "cd", 3) == 0
		|| ft_strncmp(element, "pwd", 4) == 0
		|| ft_strncmp(element, "env", 4) == 0
		|| ft_strncmp(element, "echo", 5) == 0
		|| ft_strncmp(element, "unset", 6) == 0
		|| ft_strncmp(element, "export", 7) == 0)
		return (T_BUILTIN);
	if (ft_strncmp(element, "<<", 2) == 0
		|| ft_strncmp(element, "<", 1) == 0
		|| ft_strncmp(element, ">", 1) == 0
		|| ft_strncmp(element, ">>", 2) == 0)
		return (T_REDIRECT);
	if (ft_strncmp(element, "|", 2) == 0)
		return (T_PIPE);
	else
		return (T_SYS_CMD);
}

static short	next_node(t_list **ref_current)
{
	*ref_current = (*ref_current)->next;
	if (*ref_current)
		return (get_element_type((*ref_current)->content));
	return (T_SYS_CMD);
}

static void	fill_new_token(t_token *new_token, t_list **current, short type)
{
	while (*current && type != T_PIPE)
	{
		if (type == T_REDIRECT)	
			new_token->redirect = ft_array_append(
				new_token->redirect, (*current)->content);
		else
			new_token->cmd_array = ft_array_append(
				new_token->cmd_array, (*current)->content);
		type = next_node(current);
	}
	while (new_token->type == T_REDIRECT && current)
		new_token->type = next_node(current);
}

int	tokenize(t_shell *shell)
{
	t_list	*current;
	t_token	*new_token;
	short	type;

	current = shell->line_element_head;
	type = get_element_type(current->content);
	while (current)
	{
		if (type == T_PIPE)
			next_node(&current);
		new_token = token_new(NULL, NULL, type);
		if (new_token == NULL)
			exit_clean(shell, errno, NULL);
		fill_new_token(new_token, &current, type);
		token_add_back(&shell->token_head, new_token);
	}
	// free line_element_head
	return (SUCCESS);
}
