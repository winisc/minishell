/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exit_clean(t_cmd *head, t_shell *shell, int status)
{
	cmd_clear(head);
	env_destroy(shell->env);
	rl_clear_history();
	exit(status);
}

static void	run_external(t_cmd *cmd, t_cmd *head, t_shell *shell)
{
	char	*path;
	char	**envp;
	int		code;

	path = resolve_path(cmd->argv[0], shell->env);
	if (!path)
	{
		error_msg(NULL, cmd->argv[0], "command not found");
		exit_clean(head, shell, 127);
	}
	envp = env_to_array(shell->env);
	execve(path, cmd->argv, envp);
	error_msg(NULL, cmd->argv[0], strerror(errno));
	code = 126;
	if (errno == ENOENT)
		code = 127;
	free(path);
	free_array(envp);
	exit_clean(head, shell, code);
}

static void	setup_child_pipes(t_cmd *cmd, t_pipe *p)
{
	if (p->prev_fd != -1)
	{
		dup2(p->prev_fd, STDIN_FILENO);
		close(p->prev_fd);
	}
	if (cmd->next)
	{
		close(p->pipefd[0]);
		dup2(p->pipefd[1], STDOUT_FILENO);
		close(p->pipefd[1]);
	}
}

void	child_process(t_cmd *cmd, t_cmd *head, t_shell *shell, t_pipe *p)
{
	set_signals_default();
	setup_child_pipes(cmd, p);
	if (apply_redirs(cmd->redirs) != 0)
		exit_clean(head, shell, 1);
	close_heredocs(head);
	if (!cmd->argv[0])
		exit_clean(head, shell, 0);
	if (is_builtin(cmd->argv[0]))
		exit_clean(head, shell, run_builtin(cmd, shell));
	run_external(cmd, head, shell);
}
