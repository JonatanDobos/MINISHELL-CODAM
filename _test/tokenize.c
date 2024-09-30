#include "../minishell.h"

// ! Void return ! On failure: exit_clean
static void	new_node(t_shell *shell, char *sub_line)
{
	t_list	**head_elem;
	t_list	*new_node;

	if (!sub_line)
		exit_clean(shell, errno, "new_node()");
	head_elem = &shell->line_element_head;
	new_node = ft_lstnew(sub_line);
	if (!new_node)
	{
		free(sub_line);
		exit_clean(shell, errno, "new_node()");
	}
	ft_lstadd_back(head_elem, new_node);
}

// Should it throw: error: unexpected token???
static int	isaction(char *c)
{
	if (!c)
		return (0);
	if (c[0] == '<' && c[1] == '<')
		return (2);
	if (c[0] == '>' && c[1] == '>')
		return (2);
	if (c[0] == '|' && c[1] == '|')
		return (2);
	if (c[0] == '<')
		return (1);
	if (c[0] == '>')
		return (1);
	if (c[0] == '|')
		return (1);
	return (0);
}

static int	isact_char(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

static int	isaction(char *c)
{
	if (isact_char(c[0]) && !isact_char(c[1]))
		return (1);
	if (c[0] == '<' && c[1] == '<')
	{
		if (!isact_char(c[3]))
			return (2);
		else
			return (-1);
	}
	// LEFTOFF! RESUME IF ELSE
}

// Uses basic t_list
void	tokenize(t_shell *shell, char *line)
{
	size_t	i;
	size_t	start;

	i = 0;
	start = 0;
	while (line[i])
	{
		if (isaction(line + i))
		{
			new_node(shell, ft_substr(line, start, i - start));
			start = i;
		}
		++i;
	}
}
