/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*cd_target(char **argv, t_shell *shell)
{
	char	*home;

	if (argv[1] && argv[2])
	{
		error_msg("cd", NULL, "too many arguments");
		return (NULL);
	}
	if (argv[1])
		return (argv[1]);
	home = env_get(shell->env, "HOME");
	if (!home)
		error_msg("cd", NULL, "HOME not set");
	return (home);
}

static void	cd_update(t_shell *shell, char *oldpwd)
{
	char	*cwd;

	if (oldpwd)
		env_set(&shell->env, "OLDPWD", oldpwd);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		env_set(&shell->env, "PWD", cwd);
		free(cwd);
	}
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*target;
	char	*oldpwd;

	target = cd_target(argv, shell);
	if (!target)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		error_msg("cd", target, strerror(errno));
		free(oldpwd);
		return (1);
	}
	cd_update(shell, oldpwd);
	free(oldpwd);
	return (0);
}
