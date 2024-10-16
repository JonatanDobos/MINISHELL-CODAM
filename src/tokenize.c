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

// also move this to libft
size_t	array_size(char **array)
{
	size_t	size;

	size = 0;
	while (array[size])
		++size;
	return (size);
}

// LEFTOFF SEGFAULT!!

// maybe move this to utils of libft
char	**ft_array_index_ins(char **array, char *insert, size_t index)
{
	size_t	size;
	size_t	i;
	char	**new_array;

	size = 0;
	size = array_size(array);
	new_array = (char **)malloc(sizeof(char *) * ++size);
	if (!new_array)
		return (NULL);
	new_array[size] = NULL;
	i = size - 1;
	while (size--)
	{
		printf("new: %s[%zu] %s[%zu] index: %zu\n", new_array[size], size, array[i], i, index);//test
		if (size == index)
		{
			new_array[index] = insert;
			--size;
		}
		else
			new_array[size] = array[--i];
	}
	free(array);
	return (new_array);
}

static int	add_redirect(char ***array, char *new)
{
	size_t	i;

	if (ft_strncmp(new, "<<", 2) == 0)
	{
		*array = ft_array_append(*array, new);
		return (*array == NULL);
	}
	i = 0;
	while ((*array)[i] && ft_strncmp((*array)[i], "<<", 2))
		++i;
	if (i != array_size(*array))
		*array = ft_array_index_ins(*array, new, i);
	else
		*array = ft_array_append(*array, new);
	return (*array == NULL);
}

static bool	fill_new_token(t_token *new_token, t_list **current, short *type)
{
	while (*type != T_PIPE && *current)
	{
		if (*type == T_REDIRECT)
		{
			if (add_redirect(&new_token->cmd_array, (*current)->content))
				return (EXIT_FAILURE);
		}
		else
			new_token->cmd_array = ft_array_append(
					new_token->cmd_array, (*current)->content);
		if (!new_token->cmd_array)
			return (EXIT_FAILURE);
		if (new_token->type == T_REDIRECT)
			new_token->type = *type;
		next_node(current, type);
		// free line_element node here?
	}
	return (EXIT_SUCCESS);
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
		while (type == T_PIPE && current)
		{
			next_node(&current, &type);
			// free line_element node here?
		}
		new_token = token_new(NULL, NULL, type);
		if (new_token == NULL)
			exit_clean(shell, errno, NULL);
		if (fill_new_token(new_token, &current, &type))
			exit_clean(shell, errno, NULL);
		token_add_back(&shell->token_head, new_token);
	}
	// probably free line_element_head here?
	return (SUCCESS);
}
