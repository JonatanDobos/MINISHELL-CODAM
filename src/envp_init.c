#include "../minishell.h"

// Creates linked list of env:
// ->key = "$PATH"
// ->value = "/home/lib:/etc"
char	**create_envp(char **envp)
{
	char	**array;
	int		i;

	i = 0;
	while(envp[i] != NULL)
		++i;
	array = (char **)malloc(sizeof(char *) * (i + 1));
	array[i] = NULL;
	while (i--)
	{
		array[i] = strdup(envp[i]);
		if (array[i] == NULL)
			return (ft_free_array(array), NULL);
	}
	return (array);
}
