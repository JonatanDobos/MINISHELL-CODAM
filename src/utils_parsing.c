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
