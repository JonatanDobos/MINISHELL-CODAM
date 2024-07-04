#include "../minishell.h"

// PARSING: distributing the line over t_list line_element

// ! Void return ! On failure: exit_clean
static void	ft_elem(t_shell *shell, char *sub_line)
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

static void	ft_whitespace(t_shell *shell, size_t *i, size_t *start)
{
	if (*start != *i)
		ft_elem(shell, ft_substr(shell->line, *start, *i - *start));
	*start = ++(*i);
}

// No malloc/ realloc
static char	*ft_onlyspace(char *str)
{
	size_t	i;
	size_t	new;

	if (!str)
		return (NULL);
	i = 0;
	new = 0;
	while (str[i])
	{
		if (str[i] != ' ' && ft_iswhitespace(str[i]))
		{
			while (str[i] != ' ' && ft_iswhitespace(str[i]))
				++i;
			str[new++] = ' ';
		}
		else
			str[new++] = str[i++];
	}
	str[new] = '\0';
	return (str);
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
		ft_elem(shell, ft_substr(shell->line, *start, len));
	else if (quote == '\"')
		ft_elem(shell, ft_onlyspace(ft_substr(shell->line, *start, len)));
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
			ft_whitespace(shell, &i, &start);
		else
		{
			if (shell->line[i] == '\"' || shell->line[i] == '\'')
				ft_quote(shell, &i, &start);
			else
				++i;
		}
	}
	if (start != i)
		ft_elem(shell, ft_substr(shell->line, start, i - start));
}
