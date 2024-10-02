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
			return (printf("minishell: syntax error near unexpected token \'newline\'\n"), false);
		if (istoken(line[i]) && istoken(line[i + 1]) && istoken(line[i + 2]))
			return (printf("minishell: syntax error near unexpected token \'%c\'\n", line[i + 2]), false);
		if (line[i] == '<' && line[i + 1] == '|')
			return (printf("minishell: syntax error near unexpected token \'|\'\n"), false);
		if (line[i] == '>' && line[i + 1] == '<')
			return (printf("minishell: syntax error near unexpected token \'<\'\n"), false);
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
