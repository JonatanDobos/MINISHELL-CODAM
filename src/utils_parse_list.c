#include "../minishell.h"

void	parse_list_delone(t_parse_list *node)
{
	if (node == NULL)
		return ;
	free(node->content);
	parse_list_clear(node->childlist);
	free(node);
}

void	parse_list_clear(t_parse_list **node)
{
	t_parse_list	*temp;

	if (node == NULL)
		return ;
	while (*node != NULL)
	{
		temp = (*node)->next;
		ft_nodedelone(*node);
		*node = temp;
	}
}

t_parse_list	*parse_list_new(
		t_parse_list **parentlist, t_parse_list **childlist, char *content)
{
	t_parse_list	*new;

	new = (t_parse_list *)malloc(sizeof(t_parse_list));
	if (new == NULL)
		return (NULL);
	new->childlist = childlist;
	new->parentlist = parentlist;
	new->content = content;
	new->next = NULL;
	return (new);
}

t_parse_list	*parse_list_last(t_parse_list *node)
{
	if (node != NULL)
		while (node->next != NULL)
			node = node->next;
	return (node);
}

void	parse_list_add_back(t_parse_list **node, t_parse_list *new)
{
	if (node == NULL)
		return ;
	else if (*node != NULL)
		parse_list_last(*node)->next = new;
	else
		*node = new;
}
