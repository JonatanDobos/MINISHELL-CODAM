#include "../minishell.h"

void	syntax_error(void)
{
	write(STDERR_FILENO, "Syntax Error\n", 14);
}

bool	syntax_export(char **cmd_array)
{
	char	*envar;
	int		i;

	if (!cmd_array[1])
		return (false); // exit (child) with appropriate error msg
	envar = cmd_array[1];
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
