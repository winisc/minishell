/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:56:49 by wsilveir          #+#    #+#             */
/*   Updated: 2026/04/23 19:22:16 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_u(unsigned int nbr)
{
	char	*str;
	int		res;

	str = ft_utoa(nbr);
	res = ft_putstr(str);
	free(str);
	return (res);
}
