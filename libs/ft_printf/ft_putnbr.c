/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:56:49 by wsilveir          #+#    #+#             */
/*   Updated: 2025/07/28 16:49:39 by wsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(size_t nbr)
{
	char	*str;
	int		res;

	str = ft_itoa(nbr);
	res = ft_putstr(str);
	free(str);
	return (res);
}
