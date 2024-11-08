/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_null.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:27:28 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/23 20:27:40 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_null(const char *str, char c)
{
	int	i;

	i = 0;
	if (str)
		while (str[i] || str[i] == c)
			if (str[i++] == c)
				return (i);
	return (0);
}
