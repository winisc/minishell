/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	open_redir(t_redir *r)
{
	int	fd;

	if (r->type == T_HEREDOC)
		return (r->fd);
	if (r->type == T_REDIR_IN)
		fd = open(r->target, O_RDONLY);
	else if (r->type == T_APPEND)
		fd = open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error_msg(NULL, r->target, strerror(errno));
	return (fd);
}

int	apply_redirs(t_redir *redirs)
{
	int	fd;

	while (redirs)
	{
		fd = open_redir(redirs);
		if (fd < 0)
			return (-1);
		if (redirs->type == T_REDIR_IN || redirs->type == T_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		if (redirs->type != T_HEREDOC)
			close(fd);
		redirs = redirs->next;
	}
	return (0);
}

void	close_heredocs(t_cmd *head)
{
	t_redir	*r;

	while (head)
	{
		r = head->redirs;
		while (r)
		{
			if (r->type == T_HEREDOC && r->fd >= 0)
			{
				close(r->fd);
				r->fd = -1;
			}
			r = r->next;
		}
		head = head->next;
	}
}
