#include "../minishell.h"

void	sort_envp(char **array)
{
	size_t	i;
	size_t	size;
	bool	sorted;

	size = 0;
	while (array[size] != NULL)
		++size;
	sorted = false;
	while (sorted == false)
	{
		sorted = true;
		i = 0;
		while (i < size)
		{
			if (i == size -1 && cmp_export_sort(array[0], array[i]) > 0
				|| (i < size - 1 && cmp_export_sort(array[i], array[i + 1]) > 0))
			{
				ptr_switch(&array[i], &array[i + 1]);
				sorted = false;
			}
			++i;
		}
	}
}

// Same as envp except for added quotes by strdup_export_format()
// and sorting
char	**create_envp_sorted(char **envp)
{
	char	**array;
	size_t	i;
	size_t	len;

	i = 0;
	while (envp[i] != NULL)
		++i;
	len = i;
	array = (char **)malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		array[i] = strdup_export_format(envp[i]);
		if (array[i] == NULL)
			return (ft_free_array(array), NULL);
		i++;
	}
	array[i] = NULL;
	sort_envp(array);
	return (array);
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
	new_envp[i] = strdup_export_format(envar);
	if (new_envp[i] == NULL)
		return (errno);
	*envp = new_envp;
	return (EXIT_SUCCESS);
}

static int	export_update_key(const char *envar, int i, char **envp)
{
	free(envp[i]);
	envp[i] = strdup_export_format(envar);
	if (envp[i] == NULL)
		return (errno);
	return (EXIT_SUCCESS);
}

int	export_envar_to_sorted_array(char *envar, char ***envp)
{
	char	*key;
	int		i;
	short	exit_code;

	if (export_sorted_syntax(envar) == false)
		return (EXIT_FAILURE);
	if (ft_strchr(envar, '='))
		key = ft_strdup_d(envar, '=');
	else
		key = ft_strdup(envar);
	if (key == NULL)
		return (EXIT_FAILURE);
	i = envp_key_index(*envp, key);
	exit_code = EXIT_SUCCESS;
	if ((*envp)[i] == NULL)
		exit_code = export_new_key(envar, envp);
	else if (!ft_strchr(key, '='))
		return (EXIT_SUCCESS);
	else
		exit_code = export_update_key(envar, i, *envp);
	free(key);
	if (!exit_code)
		sort_envp(*envp);
	return (exit_code);
}
