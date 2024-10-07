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
static size_t	add_element_node(t_shell *shell, size_t end, size_t start)
{
	bool	expand_success;
	char	*line;

	if (start < end)
	{
		line = ft_substr(shell->line, start, end - start);
		if (!line)
			exit_clean(shell, errno, "add_element_node");
		if (line[0] == '<' || line[0] == '>')
			ft_onlyspace(line);
		new_element(shell, line);
	}
	return (end + 1);
}

// NEEDS TESTING!! LEFTOFF
static size_t	token_element_node(t_shell *shell, char *line, size_t i)
{
	char	*sub_line;
	size_t	len;

	if (line[i] == '|' && !line[i + 1])
		return (here_doc(shell, NULL, 0), i);// needs fixing, pipe?
	if (line[i + 1] == '|')
	{
		sub_line = ft_substr(line, i, 2);
		if (!sub_line)
			exit_clean(shell, errno, "token_element_node");
		new_element(shell, sub_line);
		while (ft_iswhitespace(line[i + 2]))
			++i;
		return (i + 1);
	}
	len = skip_redir_whitespace(line + i);
	while (!ft_iswhitespace(line[i + len]) && !istoken(line[i + len])
			&& line[i + len])
		++len;
	sub_line = ft_substr(line, i, len);
	while (ft_iswhitespace(line[i + len]))
		++len;
	return (i + len - 1);
}

// Parse form input line to elent list (t_list)
void	parse_pre(t_shell *shell, char *line)
{
	size_t	i;
	size_t	start;
	char	quote;

	i = 0;
	start = i;
	quote = 0;
	while (line[i])
	{
		if (!quote && (line[i] == '\'' || line[i] =='\"'))
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		if (ft_iswhitespace(line[i]) && !quote)
			start = add_element_node(shell, i, start);
		if (istoken(line[i]) && !quote)
		{
			i += token_element_node(shell, shell->line, i);
			start = i;
		}
		++i;
	}
	add_element_node(shell, i, start);
}
