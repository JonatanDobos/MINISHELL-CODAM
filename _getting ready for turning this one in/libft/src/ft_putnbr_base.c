/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:49:58 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/22 20:47:49 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_base(long n, char *base)
{
	int			len;
	const int	size = ft_strlen(base);

	len = 0;
	if (n < 0)
	{
		len += ft_putchar('-');
		n = -n;
	}
	if (n >= size)
		len += ft_putnbr_base(n / size, base);
	len += ft_putchar(base[n % size]);
	return (len);
}
