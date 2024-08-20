#include "../minishell.h"

// ONLY SPLITS LINE INTO ELEMENTS ON:
// - whitespace - redirect - pipe

static int	isn_r(char c)
{
	if (c != '>' && c != '<')
		return (1);
	return (0);
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

// ! Void return ! On failure: exit_clean
static void	new_element(t_shell *shell, char *sub_line)
{
	t_list	**head_elem;
	t_list	*new_node;

	head_elem = &shell->line_element_head;
	if (!sub_line)
		exit_clean(shell, errno, "new_element()");
	new_node = ft_lstnew(sub_line);
	if (!new_node)
	{
		free(sub_line);
		exit_clean(shell, errno, "new_element()");
	}
	ft_lstadd_back(head_elem, new_node);
}

// Creates element node of the part between index [start] and [i]
// after splitting where needed
static void	splitter(t_shell *shell, size_t i, size_t start)
{
	bool	expand_success;
	const char	*line = ft_substr(shell->line, start, i - start);
	char	quote;

	if (!line)
		exit_clean(shell, errno, "splitter()");
	start = 0;
	i = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == quote)
			quote = 0;
		if (quote == 0 && (line[i] == '\'' || line[i] == '\"'))
			quote = line[i];
		if (quote == 0 && isaction(line + i))
			new_element(shell, ft_substr(line, start, i - start));
		if (quote == 0 && isaction(line + i))
			new_element(shell, ft_substr(line, start, i - start));
		++i;
	}
	free(line);
}

// Filters out whitespace
void	parse_line_to_element(t_shell *shell, char *line)
{
	size_t	i;
	size_t	start;

	i = 0;
	start = i;
	while (line[i])
	{
		if (ft_iswhitespace(line[i]))
		{
			if (start != i)
				splitter(shell, i, start);
			start = i + 1;
		}
		++i;
	}
	if (start != i)
		splitter(shell, i, start);
}
