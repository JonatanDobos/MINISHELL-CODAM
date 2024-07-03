#include "../minishell.h"

bool	ft_iswhitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (true);
	return (false);
}
