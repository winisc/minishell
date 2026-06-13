/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static int	is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	*append_split(char *res, char *value)
{
	int	i;

	i = 0;
	while (res && value[i])
	{
		if (is_ifs(value[i]))
			res = append_char(res, IFS_SEP);
		else
			res = append_char(res, value[i]);
		i++;
	}
	return (res);
}

void	noop_free(void *content)
{
	(void)content;
}

char	**list_to_argv(t_list *words)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (ft_lstsize(words) + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (words)
	{
		argv[i] = words->content;
		i++;
		words = words->next;
	}
	argv[i] = NULL;
	return (argv);
}
