#include "../minishell.h"

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

static bool	token_check(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (istoken(line[i]) && line[i + 1] == '\0')
			return (printf("%s\'newline\'\n", TOKEN_ERR), false);
		if (istoken(line[i]) && istoken(line[i + 1]) && istoken(line[i + 2]))
			return (printf("%s\'%c\'\n", TOKEN_ERR, line[i + 2]), false);
		if (line[i] == '<' && line[i + 1] == '|')
			return (printf("%s\'|\'\n", TOKEN_ERR), false);
		if (line[i] == '>' && line[i + 1] == '<')
			return (printf("%s\'<\'\n", TOKEN_ERR), false);
		++i;
	}
	return (true);
}

bool	syntax_pre(const char *line)
{
	if (!quote_check(line))
		return (false);
	if (!token_check(line))
		return (false);
	return (true);
}
