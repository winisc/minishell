/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	if (!ft_strncmp(name, "echo", 5) || !ft_strncmp(name, "pwd", 4)
		|| !ft_strncmp(name, "env", 4) || !ft_strncmp(name, "cd", 3)
		|| !ft_strncmp(name, "export", 7) || !ft_strncmp(name, "unset", 6)
		|| !ft_strncmp(name, "exit", 5))
		return (1);
	return (0);
}

int	run_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*name;

	name = cmd->argv[0];
	if (!ft_strncmp(name, "echo", 5))
		return (builtin_echo(cmd->argv));
	if (!ft_strncmp(name, "pwd", 4))
		return (builtin_pwd());
	if (!ft_strncmp(name, "env", 4))
		return (builtin_env(shell->env));
	if (!ft_strncmp(name, "cd", 3))
		return (builtin_cd(cmd->argv, shell));
	if (!ft_strncmp(name, "export", 7))
		return (builtin_export(cmd->argv, shell));
	if (!ft_strncmp(name, "unset", 6))
		return (builtin_unset(cmd->argv, shell));
	return (builtin_exit(cmd->argv, shell));
}
