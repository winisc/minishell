/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"

# define E_CMD_NOT_FOUND 127
# define E_NO_PERM 126

typedef struct s_pipe
{
	int		prev_fd;
	int		pipefd[2];
	pid_t	last;
}	t_pipe;

void	execute(t_cmd *cmds, t_shell *shell);
void	child_process(t_cmd *cmd, t_cmd *head, t_shell *shell, t_pipe *p);
void	exit_clean(t_cmd *head, t_shell *shell, int status);
void	parent_fds(t_pipe *p, int has_next);
int		exit_status(int status);

char	*resolve_path(char *cmd, t_env *env);

int		is_builtin(char *name);
int		run_builtin(t_cmd *cmd, t_shell *shell);

int		apply_redirs(t_redir *redirs);
void	close_heredocs(t_cmd *head);
int		process_heredocs(t_cmd *cmds, t_shell *shell);
int		is_delim(char *line, char *delim);
char	*strip_quotes(char *s);
void	heredoc_child(int *pfd, char *delim, t_cmd *head, t_shell *shell);

/* builtins */
int		builtin_echo(char **argv);
int		builtin_pwd(void);
int		builtin_env(t_env *env);
int		builtin_cd(char **argv, t_shell *shell);
int		builtin_export(char **argv, t_shell *shell);
int		builtin_unset(char **argv, t_shell *shell);
int		builtin_exit(char **argv, t_shell *shell);

#endif
