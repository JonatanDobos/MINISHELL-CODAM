#include "../minishell.h"

void	sig_arg_delone(t_sig_arg *node)
{
	if (node == NULL)
		return ;
	ft_lstclear(node->cmd_head, free);
	ft_free_array(node->cmd_array);
	free(node);
}

void	sig_arg_clear(t_sig_arg **node)
{
	t_sig_arg	*temp;

	if (node == NULL)
		return ;
	while (*node != NULL)
	{
		temp = (*node)->next;
		ft_nodedelone(*node);
		*node = temp;
	}
}

t_sig_arg	*sig_arg_new(
		t_list **cmd_head, char **cmd_array, short token)
{
	t_sig_arg	*new;

	new = (t_sig_arg *)malloc(sizeof(t_sig_arg));
	if (new == NULL)
		return (NULL);
	new->cmd_head = cmd_head;
	new->cmd_array = cmd_array;
	new->token = token;
	new->next = NULL;
	return (new);
}

t_sig_arg	*sig_arg_last(t_sig_arg *node)
{
	if (node != NULL)
		while (node->next != NULL)
			node = node->next;
	return (node);
}

void	sig_arg_add_back(t_sig_arg **node, t_sig_arg *new)
{
	if (node == NULL)
		return ;
	else if (*node != NULL)
		sig_arg_last(*node)->next = new;
	else
		*node = new;
}
