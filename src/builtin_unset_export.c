#include "../minishell.h"

void	builtin_unset(char **cmd_array, char **envp)
{
	char		*key;
	int			i;

	errno = 0;
	key = ft_strdup_d(cmd_array[1], '=');
	if (key == NULL)
		error_exit(errno, "unset");
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)))
		i++;
	if (envp[i] == NULL)
		return ;
	free(envp[i]);
	while (envp[i + 1] != NULL)
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
	free(key);
	exit(errno);
}

static void	export_new_key(const char *envar, char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	new_envp = ft_realloc_array(envp, i + 1);
	if (new_envp == NULL)
		return ;
	envp = new_envp;
	envp[i] = ft_strdup(envar);
	if (new_envp[i] == NULL)
		return ;
}

static void	export_update_key(const char *envar, int i, char **envp)
{
	free(envp[i]);
	envp[i] = ft_strdup(envar);
}

// envar should be cmd_node->content, will not be free'd in this function
void	builtin_export(char **cmd_array, char **envp)
{
	const char	*envar = cmd_array[1];
	char		*key;
	int			i;

	errno = 0;
	if (syntax_export(envar) == false)
		return (syntax_error()); // syntax_export could exit instead once pipex is in place
	key = ft_strdup_d(envar, '=');
	if (key == NULL)
		error_exit(errno, "export");
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)))
		i++;
	if (envp[i] == NULL)
		export_new_key(envar, envp);
	else
		export_update_key(envar, i, envp);
	free(key);
	exit(errno);
}
