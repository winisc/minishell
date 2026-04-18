/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:35:38 by wsilveir          #+#    #+#             */
/*   Updated: 2025/12/20 00:36:51 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_convert(char c, va_list args)
{
	if (c == '%')
		return (ft_putchar('%'));
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putnbr_pointer((size_t)va_arg(args, char *)));
	else if (c == 'u')
		return (ft_putnbr_u(va_arg(args, unsigned int)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'x' || c == 'X')
	{
		if (c == 'x')
			return (ft_putnbr_hex(va_arg(args, unsigned int), 0));
		else
			return (ft_putnbr_hex(va_arg(args, unsigned int), 1));
	}
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	size_t		i;
	va_list		args;
	int			res;

	i = 0;
	res = 0;
	if (!format)
		return (i);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && ft_strchr("cspdiuxX%", format[i + 1]))
		{
			i++;
			res += ft_print_convert((char) format[i], args);
		}
		else
			res += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (res);
}
