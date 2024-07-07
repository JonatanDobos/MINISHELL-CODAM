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

static bool	ft_expand(t_shell *shell, size_t i, size_t start)
{
	char	*envp_line;

	if (shell->line[start + 1] == '?')
		return (new_element(shell, ft_itoa(shell->last_errno)), true);
	else
	{
		envp_line = parse_envp(shell, start);
		if (envp_line)
			new_element(shell, ft_strdup(ft_strchr(envp_line, '=') + 1));
		return (true);
	}
	return (false);
}

static void	ft_whitespace(t_shell *shell, size_t i, size_t start)
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

static void	ft_quote(t_shell *shell, size_t *i, size_t *start)
{
	char	quote;
	size_t	len;

	quote = shell->line[*i];
	*start = ++(*i);
	while (shell->line[*i] != quote && shell->line[*i])
		++(*i);
	if (shell->line[*i] == '\0')
		exit_clean(shell, errno, "syntax error");
	len = *i - *start;
	if (quote == '\'')
		new_element(shell, ft_substr(shell->line, *start, len));
	else if (quote == '\"')
		new_element(shell, ft_onlyspace(ft_substr(shell->line, *start, len)));
	*start = ++(*i);
}

// Needs:
// - Testing of in quote formatting and syntax check ??
// - Pre-check on quote syntax ??
void	parse_line_to_elem(t_shell *shell)
{
	size_t	i;
	size_t	start;

	i = 0;
	start = i;
	while (shell->line[i])
	{
		if (ft_iswhitespace(shell->line[i]))
		{
			ft_whitespace(shell, i, start);
			start = ++i;
		}
		else
		{
			if (shell->line[i] == '\"' || shell->line[i] == '\'')
				ft_quote(shell, &i, &start);
			else
				++i;
		}
	}
	if (start != i)
		new_element(shell, ft_substr(shell->line, start, i - start));
}
