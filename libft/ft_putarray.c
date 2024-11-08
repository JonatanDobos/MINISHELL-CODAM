/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putarray.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 17:14:12 by jdobos        #+#    #+#                 */
/*   Updated: 2024/10/17 18:12:59 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	smallest(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

static short	print_index(int index)
{
	if (ft_putchar('[') < 0)
		return (-1);
	if (ft_putstr(ft_itoa(index)) < 0)
		return (-1);
	if (ft_putchar(']') < 0)
		return (-1);
	return (1);
}

static int	debug_mode(char **array, size_t i, int bytes, int total)
{
	if (ft_putstr("{\n") < 0)
		return (-1);
	while (array[i] && bytes >= 0)
	{
		total += bytes;
		if (print_index(i) < 0)
			return (-1);
		if (ft_putstr(" \"") < 0)
			return (-1);
		bytes = ft_putstr(array[i++]);
		if (bytes >= 0)
		{
			if (ft_putstr("\"\n") < 0)
				return (-1);
		}
	}
	if (ft_putstr("}\n") < 0)
		return (-1);
	return (smallest(total, bytes));
}

int	ft_putarray(char **array, bool debugmode)
{
	size_t	i;
	int		bytes;
	int		total;

	if (!array)
		return (ft_putstr("**array(NULL)\n"));
	if (!(*array))
		return (ft_putstr("*array(NULL)\n"));
	i = 0;
	bytes = 0;
	total = 0;
	if (debugmode)
		return (debug_mode(array, i, bytes, total));
	while (array[i] && bytes >= 0)
	{
		total += bytes;
		bytes = ft_putstr(array[i++]);
		if (bytes >= 0)
			if (ft_putstr("\n") < 0)
				return (-1);
	}
	return (smallest(total, bytes));
}
