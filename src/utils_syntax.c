#include "../minishell.h"

bool	syntax_check(const char *line)
{
	size_t	i;
	t_uint	s_quote_count;
	t_uint	d_quote_count;

	i = 0;
	s_quote_count = 0;
	d_quote_count = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			++s_quote_count;
		if (line[i] == '\"')
			++d_quote_count;
		++i;
	}
	if (s_quote_count % 2 != 0 || d_quote_count % 2 != 0)
		return (FAILURE);
	return (SUCCESS);
}
