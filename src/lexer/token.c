/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/05/31 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*token_new(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

void	token_add_back(t_token **head, t_token *new)
{
	t_token	*cur;

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

void	free_tokens(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		free(head->value);
		free(head);
		head = next;
	}
}
