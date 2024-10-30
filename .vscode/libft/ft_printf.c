/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:13:52 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/08 18:30:08 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sprint(char *str)
{
	if (str == NULL)
		return (write(1, "(null)", 6));
	else
		return (ft_putstr(str));
}

static int	ft_pprint(void *p)
{
	if (p == NULL)
		return (write(1, "(nil)", 5));
	else
		return (ft_putpointer((unsigned long)p));
}

static int	ft_spellbook(va_list args, const char *form)
{
	int	bytes_printed;

	if (*form == '%')
		return (ft_putchar('%'));
	if (*form == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (*form == 'i' || *form == 'd')
		return (ft_putnbr(va_arg(args, int)));
	if (*form == 'u')
		return (ft_putnbr(va_arg(args, unsigned int)));
	if (*form == 'x')
		return (ft_putnbr_base(va_arg(args, int),
				"0123456789abcdef"));
	if (*form == 'X')
		return (ft_putnbr_base(va_arg(args, unsigned int),
				"0123456789ABCDEF"));
	if (*form == 'p')
		return (ft_pprint(va_arg(args, void *)));
	if (*form == 's')
		return (ft_sprint(va_arg(args, char *)));
	bytes_printed = write(1, "%%", 1);
	bytes_printed += write(1, form, 1);
	return (bytes_printed);
}

int	ft_printf(const char *form, ...)
{
	va_list	args;
	int		bytes_printed;
	int		i;

	va_start(args, form);
	bytes_printed = 0;
	i = 0;
	while (form[i])
	{
		if (form[i] == '%')
			bytes_printed += ft_spellbook(args, (form + ++i));
		else
			bytes_printed += write(1, (form + i), 1);
		i++;
	}
	va_end(args);
	return (bytes_printed);
}
