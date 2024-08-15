#include "../minishell.h"

int	export_syntax(const char *envar)
{
	int		i;

	if (envar == NULL)
		return (false);
	i = 0;
	while (envar[i] && envar[i] != '=')
	{
		if (!ft_isalpha(envar[i]) && envar[i] != '_')
			return (false);
		++i;
	}
	if (ft_strchr(envar, '=') <= envar)
		return (false);
	return (true);
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
