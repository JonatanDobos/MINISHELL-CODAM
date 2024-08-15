#include "../minishell.h"

void	builtin_unset(char **cmd_array, char **envp)
{
	char		*key;
	int			i;

	key = ft_strdup_d(cmd_array[1], '=');
	if (key == NULL)
		return ;
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)))
		i++;
	if (envp[i] == NULL)
	{
		free(key);
		return ;
	}
	free(envp[i]);
	while (envp[i + 1] != NULL)
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
}

static void	export_new_key(const char *envar, char ***envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while ((*envp)[i] != NULL)
		i++;
	new_envp = ft_realloc_array(*envp, i + 1);
	if (new_envp == NULL)
		return ;
	new_envp[i] = ft_strdup(envar);
	if (new_envp[i] == NULL)
		return ;
	*envp = new_envp;
}

static void	export_update_key(const char *envar, int i, char **envp)
{
	free(envp[i]);
	envp[i] = ft_strdup(envar);
}

char	**builtin_export(char *envar, char **envp)
{
	char		*key;
	int			i;

	if (export_syntax(envar) == false)
	{
		printf("export: '%s': not a valid identifier\n", envar);
		return (envp);
	}
	key = ft_strdup_d(envar, '=');
	if (key == NULL)
		return (envp);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)))
		i++;
	if (envp[i] == NULL)
		export_new_key(envar, &envp);
	else
		export_update_key(envar, i, envp);
	free(key);
	return (envp);
}
