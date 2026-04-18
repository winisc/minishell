/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:43:59 by wsilveir          #+#    #+#             */
/*   Updated: 2025/07/28 20:20:09 by wsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	length(unsigned int num)
{
	size_t	i;

	if (num == 0)
		return (1);
	i = 0;
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_utoa(unsigned int n)
{
	size_t	len;
	int		num;
	char	*str;

	len = length(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	str[len] = 0;
	while (len > 0)
	{
		num = n % 10;
		str[--len] = num + '0';
		n = n / 10;
	}
	return (str);
}
