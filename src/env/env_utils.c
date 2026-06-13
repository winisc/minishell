/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_add_back(t_env **head, t_env *new)
{
	t_env	*cur;

	if (!*head)
	{
		*head = new;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	env_destroy(t_env *head)
{
	t_env	*next;

	while (head)
	{
		next = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = next;
	}
}

char	*env_get(t_env *head, char *key)
{
	size_t	len;

	if (!key)
		return (NULL);
	len = ft_strlen(key);
	while (head)
	{
		if (ft_strncmp(head->key, key, len + 1) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}
