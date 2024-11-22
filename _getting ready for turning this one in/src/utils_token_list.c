/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:48:34 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 18:48:37 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// !! pointers inside cmd_array are shared with shell->line_element_head !!
void	token_delone(t_token *node)
{
	if (node == NULL)
		return ;
	ft_free_array(node->cmd_array);
	ft_free_array(node->redirect);
	free(node);
}

void	token_clear(t_token **node)
{
	t_token	*temp;

	if (node == NULL)
		return ;
	while (*node != NULL)
	{
		temp = (*node)->next;
		token_delone(*node);
		*node = temp;
	}
}

t_token	*token_new(char **cmd_array, char **redirect, short type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->cmd_array = cmd_array;
	new->redirect = redirect;
	new->heredoc_pipe[0] = -1;
	new->heredoc_pipe[1] = -1;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_token	*token_last(t_token *node)
{
	if (node != NULL)
		while (node->next != NULL)
			node = node->next;
	return (node);
}

void	token_add_back(t_token **node, t_token *new)
{
	if (node == NULL)
		return ;
	else if (*node != NULL)
		token_last(*node)->next = new;
	else
		*node = new;
}
