#include "../minishell.h"

bool	istoken(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

// Returns: skip amount
size_t	skip_redir_whitespace(char *line)
{
	size_t	i;
	
	i = 0;
	while (istoken(line[i]))
		++i;
	while (ft_iswhitespace(line[i]))
		++i;
	return (i);
}
