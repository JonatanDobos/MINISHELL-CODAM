#include "../minishell.h"

static short	get_element_type(const char *element)
{
	if (ft_strncmp(element, "cd", 3) == 0
		|| ft_strncmp(element, "pwd", 4) == 0
		|| ft_strncmp(element, "env", 4) == 0
		|| ft_strncmp(element, "echo", 5) == 0
		|| ft_strncmp(element, "exit", 5) == 0
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

static void	next_node(t_list **ref_current, short *type)
{
	*ref_current = (*ref_current)->next;
	if (*ref_current)
		*type = get_element_type((*ref_current)->content);
}

static int	add_redirect(char ***array, char *new)
{
	size_t	i;

	if (*array == NULL || ft_strncmp(new, "<<", 2) == 0)
	{
		*array = ft_array_append(*array, new);
		return (*array == NULL);
	}
	i = 0;
	while ((*array)[i] && ft_strncmp((*array)[i], "<<", 2))
		++i;
	if (i != ft_array_size(*array))
		*array = ft_array_index_ins(*array, new, i);
	else
		*array = ft_array_append(*array, new);
	return (*array == NULL);
}

static bool	fill_new_token(
	t_shell *shell, t_token *new_token, t_list **current, short *type)
{
	t_list	*last;

	while (*type != T_PIPE && *current)
	{
		if (*type == T_REDIRECT)
		{
			if (add_redirect(&new_token->redirect, (*current)->content))
				return (EXIT_FAILURE);
		}
		else
			new_token->cmd_array = ft_array_append(
					new_token->cmd_array, (*current)->content);
		if (!new_token->cmd_array)
			return (EXIT_FAILURE);
		if (new_token->type == T_REDIRECT)
			new_token->type = *type;
		last = *current;
		next_node(current, type);
		free(last);
		shell->line_element_head = *current;
	}
	return (EXIT_SUCCESS);
}

// Check for leaks?
int	tokenize(t_shell *shell)
{
	t_list	*current;
	t_list	*last;
	t_token	*new_token;
	short	type;

	current = shell->line_element_head;
	type = get_element_type(current->content);
	while (current)
	{
		while (type == T_PIPE && current)
		{
			last = current;
			next_node(&current, &type);
			free(last);
			shell->line_element_head = current;
		}
		new_token = token_new(NULL, NULL, type);
		if (new_token == NULL)
			exit_clean(shell, errno, NULL);
		if (fill_new_token(shell, new_token, &current, &type))
			exit_clean(shell, errno, NULL);
		token_add_back(&shell->token_head, new_token);
	}
	ft_free_null((char **)&shell->line_element_head);
	return (SUCCESS);
}
