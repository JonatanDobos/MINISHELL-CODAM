#include "../minishell.h"

// PARSING: distributing the line over t_list line_element

// ! Void return ! On failure: exit_clean
static void	new_element(t_shell *shell, char *sub_line)
{
	t_list	**head_elem;
	t_list	*new_node;

	head_elem = &shell->line_element_head;
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

// Creates element node of the part between index [start] and [i] on 
static size_t	add_element_node(t_shell *shell, size_t i, size_t start)
{
	bool	expand_success;
	char	*line;

	if (start < i)
	{
		line = ft_substr(shell->line, start, i - start);
		if (!line)
			exit_clean(shell, errno, "add_element_node");
		new_element(shell, line);
	}
	return (i + 1);
}

static size_t	quote_element(t_shell *shell, char *line, size_t i)
{
	char	quote;
	size_t	start;

	start = i;
	quote = line[i++];
	while (line[i] && !(line[i] == quote
			&& (line[i + 1] == '\0' || ft_iswhitespace(line[i + 1]))))
		++i;
	add_element_node(shell, i + 1, start);
	return (i);
}

// Parse form input line to elent list (t_list)
void	parse_pre(t_shell *shell, char *line)
{
	size_t	i;
	size_t	start;

	i = 0;
	start = i;
	while (line[i])
	{
		if ((line[i] == '\"' || line[i] == '\'')
			&& (i == 0 || ft_iswhitespace(line[i - 1]))
			&& skip_to_end_quote(line, i))
		{
			i = quote_element(shell, line, i);
			start = i + 1;
		}
		else if (line[i] == '<' || line[i] == '>')
			i += skip_redir_whitespace(line + i);
		else if (ft_iswhitespace(line[i]) && i != 0)
			start = add_element_node(shell, i, start);
		++i;
	}
	add_element_node(shell, i, start);
}
