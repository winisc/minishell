/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:45:30 by wsilveir          #+#    #+#             */
/*   Updated: 2026/04/18 20:09:41 by wsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex(unsigned int nbr, int to)
{
	char	*base;
	int		res;

	if (to)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	res = 0;
	if (nbr >= 16)
		res += ft_putnbr_hex(nbr / 16, to);
	res += ft_putchar(base[nbr % 16]);
	return (res);
}
