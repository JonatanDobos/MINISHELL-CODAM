#include "../minishell.h"

static bool	istoken(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static bool	quote_check(const char *line)
{
	char	quote;
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				++i;
			if (line[i] != quote)
				return (false);
		}
		++i;
	}
	return (true);
}

static bool	pipe_redir_check(const char *line)
{
	char	symbol;
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (istoken(line[i]))
		{
			symbol = line[i++];
			if (line[i] && istoken(line[i + 1]))
				return (false);
			if (line[i] == '<' && line[i + 1] == '|')
				return (false);
			if (line[i] == '>' && line[i + 1] == '<')
				return (false);
		}
		++i;
	}
	return (true);
}

bool	syntax_pre(const char *line)
{
	if (!quote_check(line))
		return (false);
	if (!pipe_redir_check(line))
		return (false);
	return (true);
}
