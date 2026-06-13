/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*append_free(char *dst, char *src)
{
	char	*res;

	if (!dst)
		return (NULL);
	res = ft_strjoin(dst, src);
	free(dst);
	return (res);
}

char	*append_char(char *res, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (append_free(res, str));
}

int	is_name_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	has_quote_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}
