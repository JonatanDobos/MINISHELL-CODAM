/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnarr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:03:34 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/27 22:10:43 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// find a needle in an array of haystacks
char	*ft_strnarr(char **haystack, char *needle, size_t n)
{
	const size_t	needle_len = ft_strlen(needle);

	while (*haystack && n)
	{
		if (ft_strnstr(*haystack, needle, needle_len))
			return (*haystack);
	}
	return (NULL);
}
