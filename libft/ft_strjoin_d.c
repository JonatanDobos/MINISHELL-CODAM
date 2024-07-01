/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:37:50 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/04/30 23:44:50 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_d(const char *s1, const char *s2, const char delim)
{
	char			*ptr;
	const size_t	s1len = ft_strlen(s1);
	const size_t	s2len = ft_strlen(s2);

	ptr = (char *)malloc((s1len + s2len + 2) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, s1len + 1);
	ptr[s1len] = delim;
	ptr[s1len + 1] = '\0';
	ft_strlcat(ptr, s2, s1len + s2len + 2);
	return (ptr);
}
