/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_fields.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static int	push_word(t_list **words, char *str)
{
	t_list	*node;

	if (!str)
		return (0);
	node = ft_lstnew(str);
	if (!node)
	{
		free(str);
		return (0);
	}
	ft_lstadd_back(words, node);
	return (1);
}

static int	push_fields(t_list **words, char **fields)
{
	int	i;

	i = 0;
	while (fields[i])
	{
		if (!push_word(words, fields[i]))
		{
			i++;
			while (fields[i])
				free(fields[i++]);
			free(fields);
			return (0);
		}
		i++;
	}
	free(fields);
	return (1);
}

static char	**expand_to_fields(char *arg, t_shell *shell)
{
	char	*expanded;
	char	**fields;

	expanded = expand_arg(arg, shell, 1);
	if (!expanded)
		return (NULL);
	fields = ft_split(expanded, IFS_SEP);
	free(expanded);
	return (fields);
}

int	collect_words(t_list **words, char *arg, t_shell *shell)
{
	char	**fields;
	int		had_quote;

	had_quote = has_quote_char(arg);
	fields = expand_to_fields(arg, shell);
	if (!fields)
		return (0);
	if (!fields[0] && had_quote)
	{
		free(fields);
		return (push_word(words, ft_strdup("")));
	}
	return (push_fields(words, fields));
}
