/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*append_single(char *res, char *arg, int *i)
{
	int		start;
	char	*piece;

	(*i)++;
	start = *i;
	while (arg[*i] && arg[*i] != '\'')
		(*i)++;
	piece = ft_substr(arg, start, *i - start);
	if (arg[*i])
		(*i)++;
	if (!piece)
	{
		free(res);
		return (NULL);
	}
	res = append_free(res, piece);
	free(piece);
	return (res);
}

char	*append_double(char *res, char *arg, int *i, t_exp *exp)
{
	(*i)++;
	exp->quoted = 1;
	while (arg[*i] && arg[*i] != '"')
	{
		if (arg[*i] == '$')
			res = append_dollar(res, arg, i, exp);
		else
			res = append_char(res, arg[(*i)++]);
		if (!res)
			break ;
	}
	exp->quoted = 0;
	if (res && arg[*i])
		(*i)++;
	return (res);
}
