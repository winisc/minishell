/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	exec_single_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirs(cmd->redirs) == 0)
		shell->last_status = run_builtin(cmd, shell);
	else
		shell->last_status = 1;
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

static void	wait_pipeline(pid_t last, t_shell *shell)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = waitpid(-1, &status, 0);
	while (pid != -1)
	{
		if (pid == last)
			shell->last_status = exit_status(status);
		pid = waitpid(-1, &status, 0);
	}
}

static void	exec_pipeline(t_cmd *cmds, t_shell *shell)
{
	t_pipe	p;
	t_cmd	*cur;
	pid_t	pid;

	p.prev_fd = -1;
	p.last = -1;
	cur = cmds;
	set_signals_exec();
	while (cur)
	{
		if (cur->next && pipe(p.pipefd) < 0)
			break ;
		pid = fork();
		if (pid < 0)
			break ;
		if (pid == 0)
			child_process(cur, cmds, shell, &p);
		p.last = pid;
		parent_fds(&p, cur->next != NULL);
		cur = cur->next;
	}
	wait_pipeline(p.last, shell);
	set_signals_interactive();
}

void	execute(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return ;
	if (!process_heredocs(cmds, shell))
		return ;
	if (!cmds->next && is_builtin(cmds->argv[0]))
		exec_single_builtin(cmds, shell);
	else
		exec_pipeline(cmds, shell);
}
