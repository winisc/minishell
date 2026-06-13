/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char	*append_status(char *res, int *i, t_shell *shell)
{
	char	*value;

	(*i)++;
	value = ft_itoa(shell->last_status);
	if (!value)
	{
		free(res);
		return (NULL);
	}
	res = append_free(res, value);
	free(value);
	return (res);
}

static char	*append_var(char *res, char *arg, int *i, t_exp *exp)
{
	int		start;
	char	*name;
	char	*value;

	start = *i;
	while (is_name_char(arg[*i]))
		(*i)++;
	name = ft_substr(arg, start, *i - start);
	if (!name)
	{
		free(res);
		return (NULL);
	}
	value = env_get(exp->shell->env, name);
	free(name);
	if (!value)
		return (res);
	if (exp->split && !exp->quoted)
		return (append_split(res, value));
	return (append_free(res, value));
}

char	*append_dollar(char *res, char *arg, int *i, t_exp *exp)
{
	(*i)++;
	if (arg[*i] == '?')
		return (append_status(res, i, exp->shell));
	if (!is_name_start(arg[*i]))
		return (append_char(res, '$'));
	return (append_var(res, arg, i, exp));
}
