/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_numeric(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	long	code;

	ft_putendl_fd("exit", 2);
	if (argv[1] && !is_numeric(argv[1]))
	{
		error_msg("exit", argv[1], "numeric argument required");
		shell->exit_flag = 1;
		return (2);
	}
	if (argv[1] && argv[2])
	{
		error_msg("exit", NULL, "too many arguments");
		return (1);
	}
	shell->exit_flag = 1;
	if (!argv[1])
		return (shell->last_status);
	code = ft_long_atoi(argv[1]);
	return ((code % 256 + 256) % 256);
}
