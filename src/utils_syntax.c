#include "../minishell.h"

void	syntax_error(void)
{
	write(STDERR_FILENO, "Syntax Error\n", 14);
}

bool	syntax_export(char *envar)
{
	int		i;

	if (envar == NULL)
		return (false); // exit (child) with appropriate error msg
	i = 0;
	while (envar[i] && envar[i] != '=')
	{
		if (!ft_isalnum(envar[i]) && envar[i] != '_')
			return (false);
		++i;
	}
	if (ft_strchr(envar, '=') <= envar)
		return (false);
	return (true);
}
