/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stris.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:50:48 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/10/08 21:13:57 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// evaluate each character in string with func
// return evaluation value for first time func(c) != 0
int	ft_stris(const char *string, int (*func)(int c))
{
	size_t	i;
	int		check;

	i = 0;
	check = 0;
	while (string[i])
	{
		check = func(string[i]);
		if (check == false)
			return (false);
		i++;
	}
	return (true);
}
