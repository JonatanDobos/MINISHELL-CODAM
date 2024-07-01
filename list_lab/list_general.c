/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_general.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/26 21:57:05 by svan-hoo      #+#    #+#                 */
/*   Updated: 2024/06/28 16:16:37 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "list_types.h"

void	ft_free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		++i;
	}
	free(arr);
	arr = NULL;
}

void	*
	lstlast(
		void **head,
		t_getnext_func getnext)
{
	void	*temp;

	if (head == NULL)
		return (NULL);
	temp = *head;
	while (getnext(temp) != NULL)
		temp = getnext(temp);
	return (temp);
}

void
	lstadd_back(
		void **head,
		t_getnext_func getnext,
		void *new_node)
{
	void	*last;

	if (!head || !new_node)
		return ;
	last = lstlast(head, getnext);
	last = new_node;
}

// do we make this a general funct?
static void	string_lstfree(
	void **head)
{
	t_string_node	*tmp;
	t_string_node	*tmp_tmp;

	tmp = (t_string_node *)(*head);
	while (tmp != NULL)
	{
		free(tmp->data);
		tmp_tmp = tmp->next;
		free(tmp);
		tmp = tmp_tmp;
	}
}

static void	sig_arg_lstfree(
	void **head)
{
	t_sig_arg_node	*tmp;
	t_sig_arg_node	*tmp_tmp;

	tmp = (t_sig_arg_node *)(*head);
	while (tmp != NULL)
	{
		ft_free_array(tmp->cmd_array);
		string_lstfree((void **)tmp->cmd_head);
		tmp_tmp = tmp->next;
		free(tmp);
		tmp = tmp_tmp;
	}
}

void
	lstfree(
		void **head,
		t_getnext_func getnext)
{
	if (!head || !(*head))
		return ;
	if (getnext == getnext_string)
		string_lstfree(head);
	else if (getnext == getnext_sig_arg)
		sig_arg_lstfree(head);
}
