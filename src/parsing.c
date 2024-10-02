#include "../minishell.h"

// PARSING: distributing the line over t_list line_element

// Deletes all quotes in a string
void	delete_quotes(char *str)
{
	size_t	i;
	size_t	skip;
	int		quote;

	i = 0;
	skip = 0;
	quote = 0;
	while (str[skip])
	{
		if (!quote && (str[skip] == '\'' || str[skip] == '\"'))
		{
			quote = str[skip];
			++skip;
		}
		else if (quote && str[skip] == quote)
		{
			quote = 0;
			++skip;
		}
		else
			str[i++] = str[skip++];
	}
	str[i] = '\0';
}

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

	if (start != i)
	{
		line = ft_substr(shell->line, start, i - start);
		if (!line)
			exit_clean(shell, errno, "add_element_node");
		delete_quotes(line);
		new_element(shell, expand_env_in_str(shell, line));
	}
	return (i + 1);
}

static void	quote_handling(t_shell *shell, char *line, size_t i)
{
	char	quote;
	char	*sub_str;
	size_t	start;
	size_t	len;

	quote = line[i];
	start = ++i;
	while (line[i] != quote && line[i])
		++i;
	len = i - start;
	if (quote == '\'')
		new_element(shell, ft_substr(line, start, len));
	else if (quote == '\"')
	{
		sub_str = ft_onlyspace(ft_substr(line, start, len));
		if (!sub_str)
			exit_clean(shell, errno, NULL);
		new_element(shell, expand_env_in_str(shell, sub_str));
	}
}

static size_t	skip_to_end_quote(const char *line, size_t i)
{
	const char	quote = line[i++];

	while (line[i] && line[i] != quote)
		++i;
	return (i);
}

void	parse_line_to_element(t_shell *shell, char *line)
{
	size_t	i;
	size_t	start;

	i = 0;
	start = i;
	while (line[i])
	{
		if ((line[i] == '\"' || line[i] == '\'')
			&& (i == 0 || ft_iswhitespace(line[i - 1]))
			&& (line[skip_to_end_quote(line, i) + 1] == '\0'
			|| ft_iswhitespace(line[skip_to_end_quote(line, i) + 1])))
		{
			quote_handling(shell, line, i);
			i = skip_to_end_quote(line, i);
			start = i + 1;
		}
		else if (line[i] == '<' || line[i] == '>')
			i += skip_redir_whitespace(line + i);
		else if (ft_iswhitespace(line[i]) && i != 0)
			start = add_element_node(shell, i, start);
		++i;
	}
	if (start != i)
		add_element_node(shell, i, start);
}
