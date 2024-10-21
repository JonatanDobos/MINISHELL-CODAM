#include "../minishell.h"

// replicates bash's syntax for valid envp KEYs/identifiers
int	export_syntax(const char *envar)
{
	int	i;

	if (envar == NULL || !envar[0])
		return (false);
	i = 0;
	if (!ft_isalpha(envar[i]) && envar[i] != '_')
		return (false);
	++i;
	while (envar[i] && envar[i] != '=')
	{
		if (!ft_isalnum(envar[i]) && envar[i] != '_')
			return (false);
		++i;
	}
	if (i <= 1)
		return (false);
	if (envar[i] != '=')
		return (false);
	return (true);
}

int	unset_syntax(const char *envar)
{
	int	i;

	i = 0;
	if (!ft_isalpha(envar[i]) && envar[i] != '_')
		return (false);
	++i;
	while (envar[i] && envar[i] != '=')
	{
		if (!ft_isalnum(envar[i]) && envar[i] != '_')
			return (false);
		++i;
	}
	if (envar[i] == '=')
		return (false);
	return (true);
}

// points to the value behind given kye inside envp, not malloc'd
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

// Prints the sorted envp list
int	print_export_list(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
