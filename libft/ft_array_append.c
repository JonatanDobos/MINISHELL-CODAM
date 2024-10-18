/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_array_append.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/27 21:31:21 by svan-hoo      #+#    #+#                 */
/*   Updated: 2024/10/18 16:41:40 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_array_append(char **array, char *add)
{
	char	**new;
	size_t	size;

	size = 0;
	while (array && array[size])
		++size;
	new = (char **)malloc(sizeof(char *) * (size + 1 + 1));
	if (new == NULL)
		return (ft_free_array(array), NULL);
	new[size] = add;
	new[size + 1] = NULL;
	while (size--)
		new[size] = array[size];
	free(array);
	return (new);
}
