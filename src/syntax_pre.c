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

static bool	check_token_folowup(const char *line)
{
	size_t		i;
	size_t		j;
	const char	not_allowed[2] = ";";

	i = 0;
	while (istoken(line[i]))
		++i;
	while (ft_iswhitespace(line[i]))
		++i;
	if (!line[i])
		return (printf("%s\'newline\'\n", TOKEN_ERR), false);
	if (istoken(line[i]))
		return (printf("%s\'%c\'\n", TOKEN_ERR, line[i]), false);
	j = 0;
	while (not_allowed[j])
	{
		if (not_allowed[j++] == line[i])
			return (printf("%s\'%c\'\n", TOKEN_ERR, line[i]), false);
	}
	return (true);
}

static bool	check_for_pipe_continue(const char *line, size_t i)
{
	if (line[i++] == '|')
	{
		while (ft_iswhitespace(line[i]))
			++i;
		if (!line[i])
			return (true);
	}
	return (false);
}

static bool	token_check(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '|')
			return (printf("%s\'|\'\n", TOKEN_ERR), false);
		if (line[i] == '>' && line[i + 1] == '<')
			return (printf("%s\'<\'\n", TOKEN_ERR), false);
		if (line[i] == '|' && (line[i + 1] == '<' || line[i + 1] == '>'))
			return (printf("%s\'%c\'\n", TOKEN_ERR, line[i + 1]), false);
		if (istoken(line[i]))
		{
			if (check_for_pipe_continue(line, i))
				return (true);
			if (!check_token_folowup(line + i))
				return (false);
			while (istoken(line[i]))
				++i;
		}
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
