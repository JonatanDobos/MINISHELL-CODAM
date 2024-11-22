/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 23:45:15 by simon             #+#    #+#             */
/*   Updated: 2024/11/22 20:47:49 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strcat(char *dest, const char *src)
{
	const int	dlen = ft_strlen(dest);
	const int	slen = ft_strlen(src);
	int			i;

	i = 0;
	while (i < slen)
	{
		dest[dlen + i] = src[i];
		i++;
	}
	return (i);
}
