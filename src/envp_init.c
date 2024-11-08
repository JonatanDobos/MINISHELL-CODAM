#include "../minishell.h"

char	**create_envp(char **envp)
{
	char	**array;
	int		i;
	int		len;

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
		array[i] = ft_strdup(envp[i]);
		if (array[i] == NULL)
			return (ft_free_array(array), NULL);
		i++;
	}
	array[i] = NULL;
	return (array);
}
