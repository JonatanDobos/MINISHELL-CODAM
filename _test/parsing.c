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

// Returns: amount of characters to skip, or -1 if error unexpected token
static int	isaction(char *c)
{
	if (!istoken(c[0]))
		return (0);
	if (istoken(c[0]) && !istoken(c[1]))
		return (1);
	if ((c[0] == '<' && istoken(c[1]) && c[1] != '|')
		|| (c[0] == '>' && istoken(c[1]) && c[1] != '<')
		|| (c[0] == '|' && istoken(c[1])))
	{
		if (!istoken(c[3]))
			return (2);
		else
			return (-9999);// segfault test
	}
	return (0);
}

// Uses basic t_list
void	split_line_per_token(t_shell *shell, char *line)
{
	size_t	i;
	size_t	start;
	char	quote;

	i = 0;
	start = 0;
	quote = 0;
	while (line[i])
	{
		if (quote == 0 && line[i] == '\'' || line[i] == '\"')
			quote = line[i++];
		if (line[i] == quote)
			quote = 0;
		else if (quote == 0 && isaction(line + i))
		{
			new_node(shell, ft_substr(line, start, i - start));
			start = i;
		}
		++i;
	}
	if (start < i)
		new_node(shell, ft_substr(line, start, i - start));
}
