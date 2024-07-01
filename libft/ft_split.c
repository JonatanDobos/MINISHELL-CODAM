/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:38:08 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/19 18:23:47 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_splitcount(const char *s, const char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*ft_splitdup(const char *s, const char c)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	ptr = (char *)malloc((i + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[i] = '\0';
	while (i--)
		ptr[i] = s[i];
	return (ptr);
}

static void	*ft_freeall(char **array, int row)
{
	while (row--)
		free(array[row]);
	free(array);
	return (NULL);
}

char	**ft_split(const char *s, const char c)
{
	char	**array;
	int		row;
	int		i;

	row = 0;
	i = 0;
	array = (char **)malloc((ft_splitcount(s, c) + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			array[row] = ft_splitdup((char *)(s + i), c);
			if (array[row] == NULL)
				return (ft_freeall(array, row));
			i += ft_strlen(array[row]);
			row++;
		}
	}
	array[row] = NULL;
	return (array);
}
