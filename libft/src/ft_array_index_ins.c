/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_index_ins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:06:20 by joni              #+#    #+#             */
/*   Updated: 2024/11/22 20:47:49 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_array_index_ins(char **array, char *insert, size_t index)
{
	size_t	size;
	size_t	i;
	char	**new_array;

	size = 0;
	size = ft_array_size(array);
	new_array = (char **)malloc(sizeof(char *) * (++size + 1));
	if (!new_array)
		return (NULL);
	new_array[size] = NULL;
	i = size - 1;
	while (size--)
	{
		if (size == index)
			new_array[index] = insert;
		else
			new_array[size] = array[--i];
	}
	free(array);
	return (new_array);
}
