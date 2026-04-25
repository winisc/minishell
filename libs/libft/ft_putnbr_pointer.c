/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:45:30 by wsilveir          #+#    #+#             */
/*   Updated: 2026/04/23 19:22:16 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_pointer(size_t nbr)
{
	char	*base;
	int		res;

	base = "0123456789abcdef";
	res = 0;
	if (!nbr)
		return (ft_putstr("(nil)"));
	if (nbr >= 16)
	{
		res += ft_putnbr_pointer(nbr / 16);
		res += ft_putnbr_pointer(nbr % 16);
	}
	else
	{
		res += ft_putstr("0x");
		res += ft_putchar(base[nbr]);
	}
	return (res);
}
