#include "../minishell.h"

void	sig_arg_delone(t_token *node)
{
	if (node == NULL)
		return ;
	ft_lstclear(node->element_head, free);
	ft_free_array(node->cmd_array);
	free(node);
}

void	sig_arg_clear(t_token **node)
{
	t_token	*temp;

	if (node == NULL)
		return ;
	while (*node != NULL)
	{
		temp = (*node)->next;
		ft_nodedelone(*node);
		*node = temp;
	}
}

t_token	*sig_arg_new(
		t_list **element_head, char **cmd_array, short type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->element_head = element_head;
	new->cmd_array = cmd_array;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_token	*sig_arg_last(t_token *node)
{
	if (node != NULL)
		while (node->next != NULL)
			node = node->next;
	return (node);
}

void	sig_arg_add_back(t_token **node, t_token *new)
{
	if (node == NULL)
		return ;
	else if (*node != NULL)
		sig_arg_last(*node)->next = new;
	else
		*node = new;
}
