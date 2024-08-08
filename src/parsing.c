#include "../minishell.h"

// PARSING: distributing the line over t_list line_element

// Deletes all quotes in a string
void	delete_quotes()
{

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

static bool	ft_expand(t_shell *shell, size_t i, size_t start)
{
	char	*envp_line;

	if (shell->line[start + 1] == '?')
		return (new_element(shell, ft_itoa(shell->last_errno)), true);
	else
	{
		envp_line = parse_envp(shell->envp, shell->line, start);
		if (envp_line)
			new_element(shell, ft_strdup(envp_line));
		return (true);
	}
	return (false);
}

// Creates element node of the part between index [start] and [i] on 
static void	add_element_node(t_shell *shell, size_t i, size_t start)
{
	bool	expand_success;

	if (start != i)
	{
		expand_success = false;
		if (shell->line[start] == '$')
			expand_success = ft_expand(shell, i, start);
		if (!expand_success)
			new_element(shell, ft_substr(shell->line, start, i - start));
	}
}

static bool	quote_handling(t_shell *shell, char *line, size_t i)
{
	char	quote;
	char	*sub_str;
	size_t	start;
	size_t	len;

	quote = line[i];
	start = ++(i);
	while (line[i] != quote && line[i])
		++(i);
	if (line[i] == '\0')
		return (syntax_error(), false);
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
	return (true);
}

static size_t	skip_to_end_quote(char *str)
{
	size_t		skip_amount;
	const char	quote = *str;

	skip_amount = 0;
	while (str[skip_amount] && str[skip_amount] != quote)
		++skip_amount;
	return (skip_amount + 1);
}

bool	parse_line_to_element(t_shell *shell, char *line)
{
	size_t	i;
	size_t	start;

	i = 0;
	start = i;
	while (line[i])
	{
		if ((line[i] == '\"' || line[i] == '\'')
			&& (i == 0 || ft_iswhitespace(line[i - 1])))
		{
			if (!quote_handling(shell, line, i))
				return (false);
			skip_to_end_quote(line + i);
		}
		if (ft_iswhitespace(line[i]))
		{
			add_element_node(shell, i, start);
			start = ++i;
		}
		else
			++i;
	}
	if (start != i)
		add_element_node(shell, i, start);
	return (true);
}
