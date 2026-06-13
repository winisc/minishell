/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_size(t_env *head)
{
	int	n;

	n = 0;
	while (head)
	{
		n++;
		head = head->next;
	}
	return (n);
}

static char	*make_entry(t_env *node)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin(node->key, "=");
	if (!tmp)
		return (NULL);
	entry = ft_strjoin(tmp, node->value);
	free(tmp);
	return (entry);
}

char	**env_to_array(t_env *head)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (env_size(head) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (head)
	{
		if (head->value)
		{
			arr[i] = make_entry(head);
			if (!arr[i])
			{
				free_array(arr);
				return (NULL);
			}
			i++;
		}
		head = head->next;
	}
	arr[i] = NULL;
	return (arr);
}
