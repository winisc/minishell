/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	redir_add_back(t_redir **head, t_redir *new)
{
	t_redir	*cur;

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

int	add_redir(t_cmd *cmd, t_token_type type, char *target)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (0);
	redir->type = type;
	redir->target = ft_strdup(target);
	if (!redir->target)
	{
		free(redir);
		return (0);
	}
	redir->fd = -1;
	redir->next = NULL;
	redir_add_back(&cmd->redirs, redir);
	return (1);
}

void	redir_clear(t_redir *head)
{
	t_redir	*next;

	while (head)
	{
		next = head->next;
		if (head->fd >= 0)
			close(head->fd);
		free(head->target);
		free(head);
		head = next;
	}
}
