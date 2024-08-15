#include "../minishell.h"

bool	syntax_pre(const char *line)
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
