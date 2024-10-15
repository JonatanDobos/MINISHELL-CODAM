/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_islower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 19:55:21 by joni          #+#    #+#                 */
/*   Updated: 2024/10/14 19:55:30 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_islower(unsigned char c)
{
	return (c >= 'a' && c <= 'z');
}