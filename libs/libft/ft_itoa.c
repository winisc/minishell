/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:43:59 by wsilveir          #+#    #+#             */
/*   Updated: 2025/07/28 20:18:59 by wsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	length(int num)
{
	int	i;

	i = 0;
	if (num <= 0)
		i++;
	while (num != 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		ne;
	int		len;
	int		num;
	char	*str;

	len = length(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	str[len] = 0;
	ne = (n < 0);
	while (len > 0)
	{
		num = n % 10;
		if (ne)
			num = -num;
		str[--len] = num + '0';
		n = n / 10;
	}
	if (ne)
		str[0] = '-';
	return (str);
}
