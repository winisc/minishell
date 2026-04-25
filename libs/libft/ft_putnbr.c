/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:56:49 by wsilveir          #+#    #+#             */
/*   Updated: 2026/04/23 19:22:16 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(size_t nbr)
{
	char	*str;
	int		res;

	str = ft_itoa(nbr);
	res = ft_putstr(str);
	free(str);
	return (res);
}
