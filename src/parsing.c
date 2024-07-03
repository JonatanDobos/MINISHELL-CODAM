#include "../minishell.h"

// PARSING: distributing the line over t_list line_element

// ! Void return ! On failure: exit_clean
static void	line_to_elem(t_shell *shell, char *sub_line)
{
	const t_list	**head_elem = &shell->line_element_head;
	t_list			*new_node;

	if (!sub_line)
		exit_clean(shell, errno, NULL);
	new_node = ft_lstnew(sub_line);
	if (!new_node)
	{
		free(sub_line);
		exit_clean(shell, errno, NULL);
	}
	ft_lstadd_back(head_elem, new_node);
}

static void	ft_whitespace(t_shell *shell, size_t *i, size_t *start)
{
	if (*start != *i)
		line_to_elem(shell, ft_substr(shell->line, *start, *i - *start));
	*start = ++(*i);
}

static void	ft_quote(t_shell *shell, size_t *i, size_t *start)
{
	char	quote;

	quote = shell->line[*i];
	*start = ++(*i);
	while (shell->line[*i] != quote)
		++(*i);
	line_to_elem(shell, ft_substr(shell->line, start, i - start));
	*start = *i;
}

void	parse_line_to_elem(t_shell *shell)
{
	size_t	i;
	size_t	start;

	i = 0;
	start = i;
	while (shell->line[i])
	{
		if (ft_iswhitespace(shell->line[i]))
			ft_whitespace(shell, &i, &start);
		else if (shell->line[i] == '\"' || shell->line[i] == '\'')
			ft_quote(shell, &i, &start);
		else
			++i;
	}
}
