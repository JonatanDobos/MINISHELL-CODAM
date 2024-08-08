#include "../minishell.h"

int	create_cmd_array(t_token *token)
{
	t_list	*element;
	int		i;

	element = token->element_head;
	token->cmd_array = malloc(sizeof(char *) * ft_lstsize(element) + 1);
	if (token->cmd_array == NULL)
		return (FAILURE);
	while (element != NULL)
	{
		token->cmd_array[i] = element->content;
		element = element->next;
		++i;
	}
	token->cmd_array[i] = NULL;
	return (SUCCESS);
}

char	*get_env(char **envp, char *key)
{
	int		i;
	char	*ret;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)))
		++i;
	ret = envp[i];
	if (ret != NULL)
		while (*ret != '=')
			++ret;
	return (ret);
}
