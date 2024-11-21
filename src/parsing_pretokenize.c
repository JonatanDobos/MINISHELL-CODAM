/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_pretokenize.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 18:47:50 by svan-hoo      #+#    #+#                 */
/*   Updated: 2024/11/21 16:55:05 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// PARSING: distributing the line over t_list line_element

// ! Void return ! On failure: exit_clean
static void	new_element(t_shell *shell, char *sub_line)
{
	t_list	**head_elem;
	t_list	*new_node;

	if (!sub_line)
		exit_clean(shell, errno, NULL);
	head_elem = &shell->line_element_head;
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

static size_t	pipe_sub_line(t_shell *shell, char *line, size_t i)
{
	char	*sub_line;

	if (!line[i + 1])
		return (i + 1);
	sub_line = ft_substr(line, i, 1);
	if (!sub_line)
		exit_clean(shell, errno, "token_element_node");
	new_element(shell, sub_line);
	while (ft_iswhitespace(line[i + 1]))
		++i;
	return (i + 1);
}

// NEEDS TESTING!! LEFTOFF
static size_t	token_element_node(
	t_shell *shell, char *line, size_t i, size_t start)
{
	size_t	len;

	add_element_node(shell, i, start);
	if (line[i] == '|')
		return (pipe_sub_line(shell, line, i));
	len = skip_redir_ws(line + i);
	while (!ft_iswhitespace(line[i + len]) && !istoken(line[i + len])
		&& line[i + len])
	{
		if (line[i + len] == '\'' || line[i + len] == '\"')
			len = skip_to_next_quote(line, i + len) - i;
		if (line[i + len])
			++len;
	}
	new_element(shell, ft_substr(line, i, len));
	while (ft_iswhitespace(line[i + len]))
		++len;
	return (i + len);
}

// MAYBE USE SKIP_QUOTES
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
		if (!quote && (line[i] == '\'' || line[i] == '\"'))
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		if (ft_iswhitespace(line[i]) && !quote)
			start = add_element_node(shell, i, start);
		if (istoken(line[i]) && !quote)
		{
			i = token_element_node(shell, shell->line, i, start);
			start = i;
		}
		else
			++i;
	}
	add_element_node(shell, i, start);
}
