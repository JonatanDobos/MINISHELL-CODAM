#include "../minishell.h"

void	builtin_unset(char **cmd_array, char **envp)
{
	char		*key;
	int			i;

	errno = 0;
	key = ft_strdup_d(cmd_array[1], '=');
	if (key == NULL)
		error_exit(errno, "builtin_unset -> ft_strdup_d");
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)))
		i++;
	if (envp[i] == NULL)
	{
		free(key);
		exit(SUCCESS);
	}
	free(envp[i]);
	while (envp[i + 1] != NULL)
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
	exit(errno);
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
		error_exit(errno, "export_new_key -> ft_realloc_array");
	new_envp[i] = ft_strdup(envar);
	if (new_envp[i] == NULL)
		error_exit(errno, "export_new_key -> ft_strdup");
	*envp = new_envp;
}

static void	export_update_key(const char *envar, int i, char **envp)
{
	free(envp[i]);
	envp[i] = ft_strdup(envar);
	if (envp[i] == NULL)
		error_exit(errno, "export_update_key -> ft_strdup");
}

void	builtin_export(char **cmd_array, t_shell *shell)
{
	const char	*envar = cmd_array[1];
	char		*key;
	int			i;

	errno = 0;
	syntax_export(envar);
	key = ft_strdup_d(envar, '=');
	if (key == NULL)
		error_exit(errno, "builtin_export");
	i = 0;
	while (shell->envp[i] && ft_strncmp(shell->envp[i], key, ft_strlen(key)))
		i++;
	if (shell->envp[i] == NULL)
		export_new_key(envar, &shell->envp);
	else
		export_update_key(envar, i, shell->envp);
	printf("%s%s\n", key, get_env(shell->envp, envar));
	builtin_env(shell->envp);
	free(key);
	exit(errno);
}
