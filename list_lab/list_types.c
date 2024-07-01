/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:20:30 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/27 19:42:15 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_types.h"

// this should also be in libft
// >
t_string_node	*
	new_node_string(char *data)
{
	t_string_node	*new_node;

	new_node = malloc(sizeof(t_string_node));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->next = NULL;
	return (new_node);
}

void	*getnext_string(void *node)
{
	return (((t_string_node *)node)->next);
}
// <

t_sig_arg_node	*
	new_node_sig_arg(t_list **cmd_head, char **cmd_array, short token)
{
	t_sig_arg_node	*new_node;

	new_node = malloc(sizeof(t_sig_arg_node));
	if (!new_node)
		return (NULL);
	new_node->cmd_head = cmd_head;
	new_node->cmd_array = cmd_array;
	new_node->token = token;
	new_node->next = NULL;
	return (new_node);
}

void	*getnext_sig_arg(void *node)
{
	return (((t_sig_arg_node *)node)->next);
}
