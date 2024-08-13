#include "../minishell.h"

void	syntax_error(void)
{
	write(STDERR_FILENO, "Syntax Error\n", 14);
}

void	syntax_export(const char *envar)
{
	int		i;

	if (envar == NULL)
		error_exit(EINVAL, envar); // exit (child) with appropriate error msg (see bash output)
	i = 0;
	while (envar[i] && envar[i] != '=')
	{
		if (!ft_isalnum(envar[i]) && envar[i] != '_')
			error_exit(EINVAL, envar);
		++i;
	}
	if (ft_strchr(envar, '=') <= envar)
		error_exit(EINVAL, envar);
	return ;
}

char	*get_env(char **envp, const char *key)
{
	int		i;
	char	*ret;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)))
		++i;
	ret = envp[i];
	if (ret != NULL)
		while (*ret++ != '=')
			;
	return (ret);
}
