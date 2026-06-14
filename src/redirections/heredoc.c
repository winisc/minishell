/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	heredoc_wait(t_redir *r, int *pipefd, pid_t pid, t_shell *shell)
{
	int	status;

	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) != 0))
	{
		close(pipefd[0]);
		g_signal = SIGINT;
		shell->last_status = 130;
		return (0);
	}
	r->fd = pipefd[0];
	return (1);
}

static int	read_heredoc(t_redir *r, t_cmd *head, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		return (0);
	pid = fork();
	if (pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (0);
	}
	if (pid == 0)
		heredoc_child(pipefd, r->target, head, shell);
	return (heredoc_wait(r, pipefd, pid, shell));
}

int	process_heredocs(t_cmd *cmds, t_shell *shell)
{
	t_redir	*r;
	t_cmd	*c;

	set_signals_exec();
	c = cmds;
	while (c)
	{
		r = c->redirs;
		while (r)
		{
			if (r->type == T_HEREDOC && !read_heredoc(r, cmds, shell))
			{
				set_signals_interactive();
				return (0);
			}
			r = r->next;
		}
		c = c->next;
	}
	set_signals_interactive();
	return (1);
}
