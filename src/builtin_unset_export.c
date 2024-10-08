#include "../minishell.h"

int	builtin_unset(char *envar, char **envp)
{
	char		*key;
	int			i;

	if (envar == NULL)
		return (EXIT_SUCCESS);
	key = ft_strdup_d(envar, '=');
	if (key == NULL)
		return (errno);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)))
		i++;
	if (envp[i] == NULL)
	{
		free(key);
		return (EXIT_SUCCESS);
	}
	free(envp[i]);
	while (envp[i + 1] != NULL)
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
	return (EXIT_SUCCESS);
}

static int	export_new_key(const char *envar, char ***envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while ((*envp)[i] != NULL)
		i++;
	new_envp = ft_realloc_array(*envp, i + 1);
	if (new_envp == NULL)
		return (errno);
	new_envp[i] = ft_strdup(envar);
	if (new_envp[i] == NULL)
		return (errno);
	*envp = new_envp;
	return (EXIT_SUCCESS);
}

static int	export_update_key(const char *envar, int i, char **envp)
{
	free(envp[i]);
	envp[i] = ft_strdup(envar);
	if (envp[i] == NULL)
		return (errno);
	return (EXIT_SUCCESS);
}

int	builtin_export(char *envar, char ***envp)
{
	char	*key;
	int		i;
	short	exit_code;

	if (export_syntax(envar) == false)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(envar, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	key = ft_strdup_d(envar, '=');
	if (key == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while ((*envp)[i] && ft_strncmp((*envp)[i], key, ft_strlen(key)))
		i++;
	exit_code = EXIT_SUCCESS;
	if ((*envp)[i] == NULL)
		exit_code = export_new_key(envar, envp);
	else
		exit_code = export_update_key(envar, i, *envp);
	free(key);
	return (exit_code);
}
