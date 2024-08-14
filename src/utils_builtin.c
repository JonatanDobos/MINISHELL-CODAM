#include "../minishell.h"

void	syntax_error(void)
{
	write(STDERR_FILENO, "Syntax Error\n", 14);
}

bool	syntax_export(const char *envar)
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

char	*get_env(char **envp, char *key)
{
	int		i;
	char	*ret;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)))
		++i;
	ret = envp[i];
	if (ret != NULL)
		while (*ret != '=')
			++ret;
	return (++ret);
}
