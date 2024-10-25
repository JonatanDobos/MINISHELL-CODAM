/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_null.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/23 20:24:45 by svan-hoo      #+#    #+#                 */
/*   Updated: 2024/10/25 13:04:24 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_null(char **pp)
{
	if (pp != NULL && *pp != NULL)
	{
		free(*pp);
		*pp = NULL;
	}
	return (NULL);
}
