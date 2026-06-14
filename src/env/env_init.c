/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/13 17:21:56 by wsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_split_pair(char *str, char **key, char **value)
{
	int	eq;

	eq = 0;
	while (str[eq] && str[eq] != '=')
		eq++;
	*key = ft_substr(str, 0, eq);
	if (!*key)
		return (0);
	if (str[eq] == '=')
		*value = ft_strdup(str + eq + 1);
	else
		*value = ft_strdup("");
	if (!*value)
	{
		free(*key);
		return (0);
	}
	return (1);
}

static t_env	*env_new(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

static t_env	*env_new_from_str(char *str)
{
	char	*key;
	char	*value;
	t_env	*node;

	if (!env_split_pair(str, &key, &value))
		return (NULL);
	node = env_new(key, value);
	if (!node)
	{
		free(key);
		free(value);
		return (NULL);
	}
	return (node);
}

t_env	*env_init(char **envp)
{
	t_env	*head;
	t_env	*node;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		node = env_new_from_str(envp[i]);
		if (!node)
		{
			env_destroy(head);
			return (NULL);
		}
		env_add_back(&head, node);
		i++;
	}
	return (head);
}
