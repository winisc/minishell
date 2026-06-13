/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_valid_id(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_list(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		if (env->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
	return (0);
}

static int	export_one(char *arg, t_shell *shell)
{
	char	*eq;
	char	*key;
	int		ok;

	if (!is_valid_id(arg))
	{
		error_msg("export", arg, "not a valid identifier");
		return (1);
	}
	eq = ft_strchr(arg, '=');
	if (!eq)
		return (!env_set(&shell->env, arg, NULL));
	key = ft_substr(arg, 0, eq - arg);
	if (!key)
		return (1);
	ok = env_set(&shell->env, key, eq + 1);
	free(key);
	return (!ok);
}

int	builtin_export(char **argv, t_shell *shell)
{
	int	i;
	int	status;

	if (!argv[1])
		return (export_list(shell->env));
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (export_one(argv[i], shell))
			status = 1;
		i++;
	}
	return (status);
}
