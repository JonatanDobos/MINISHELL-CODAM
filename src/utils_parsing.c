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

// Skips to next instance of given quote
// Returns: absolute index next quote || 0 on no next quote
size_t	skip_to_next_quote(const char *line, size_t i)
{
	const char	quote = line[i++];

	while (line[i] && line[i] != quote)
		++i;
	if (line[i] == '\0')
		return (0);
	return (i);
}

// Skips to last instance of given quote, meaning:
// (index after last quote = \0 or whitespace)
// Returns: absolute index end quote || 0 on no end quote
size_t	skip_to_end_quote(const char *line, size_t i)
{
	const char	quote = line[i++];

	while (line[i] && !(line[i] == quote
			&& (line[i + 1] == '\0' || ft_iswhitespace(line[i + 1]))))
		++i;
	if (line[i] == '\0')
		return (0);
	return (i);
}
