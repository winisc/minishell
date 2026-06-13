/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*env_make(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = NULL;
	node->next = NULL;
	if (value)
		node->value = ft_strdup(value);
	if (!node->key || (value && !node->value))
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	return (node);
}

static t_env	*env_find(t_env *head, char *key)
{
	size_t	len;

	len = ft_strlen(key);
	while (head)
	{
		if (ft_strncmp(head->key, key, len + 1) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

static int	env_replace(t_env *node, char *value)
{
	char	*dup;

	dup = NULL;
	if (value)
		dup = ft_strdup(value);
	if (value && !dup)
		return (0);
	free(node->value);
	node->value = dup;
	return (1);
}

int	env_set(t_env **head, char *key, char *value)
{
	t_env	*node;

	node = env_find(*head, key);
	if (node)
		return (env_replace(node, value));
	node = env_make(key, value);
	if (!node)
		return (0);
	env_add_back(head, node);
	return (1);
}

int	env_unset(t_env **head, char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = *head;
	prev = NULL;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*head = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}
	return (1);
}
