/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*cmd_new(int argc)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	ft_bzero(cmd->argv, sizeof(char *) * (argc + 1));
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*cur;

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

void	cmd_free(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);
	redir_clear(cmd->redirs);
	free(cmd);
}

void	cmd_clear(t_cmd *head)
{
	t_cmd	*next;

	while (head)
	{
		next = head->next;
		cmd_free(head);
		head = next;
	}
}
