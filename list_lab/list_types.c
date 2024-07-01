/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:20:30 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/07/01 19:21:45 by svan-hoo         ###   ########.fr       */
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

t_token_node	*
	new_node_sig_arg(t_list **element_head, char **cmd_array, short token)
{
	t_token_node	*new_node;

	new_node = malloc(sizeof(t_token_node));
	if (!new_node)
		return (NULL);
	new_node->element_head = element_head;
	new_node->cmd_array = cmd_array;
	new_node->token = token;
	new_node->next = NULL;
	return (new_node);
}

void	*getnext_token(void *node)
{
	return (((t_token_node *)node)->next);
}
