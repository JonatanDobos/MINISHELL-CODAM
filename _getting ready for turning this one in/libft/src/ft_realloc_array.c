/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:31:21 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/22 20:47:49 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_realloc_array(char **array, size_t size)
{
	char	**new;

	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (new == NULL)
		return (NULL);
	new[size] = NULL;
	while (size--)
	{
		new[size] = array[size];
	}
	free(array);
	return (new);
}
