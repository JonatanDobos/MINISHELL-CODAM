/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_MISC.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:45:55 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 18:45:59 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Frees pointer array of given size, ignors NULL pointers
void	free_array_size(void **array, size_t size)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (i < size)
	{
		if (array[i])
			free(array[i++]);
	}
	free(array);
}

// size = full size of array (potential terminator included!)
void	null_set_pointerarray(void **array, size_t size)
{
	size_t	i;

	i = 0;
	while (i <= size)
		array[i++] = NULL;
}
