/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:11:17 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/08 19:21:18 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// includes delimiter \d\0
char	*ft_strdup_d(const char *str, const char delim)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while (str[i] && str[i] != delim)
		i++;
	ptr = malloc((i + 1 + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != delim)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i++] = delim;
	ptr[i] = '\0';
	return (ptr);
}
