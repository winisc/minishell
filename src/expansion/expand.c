/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*expand_arg(char *arg, t_shell *shell, int split)
{
	t_exp	exp;
	char	*res;
	int		i;

	exp.shell = shell;
	exp.split = split;
	exp.quoted = 0;
	res = ft_strdup("");
	i = 0;
	while (res && arg[i])
	{
		if (arg[i] == '\'')
			res = append_single(res, arg, &i);
		else if (arg[i] == '"')
			res = append_double(res, arg, &i, &exp);
		else if (arg[i] == '$')
			res = append_dollar(res, arg, &i, &exp);
		else
			res = append_char(res, arg[i++]);
	}
	return (res);
}

static int	expand_argv(t_cmd *cmd, t_shell *shell)
{
	t_list	*words;
	char	**new_argv;
	int		i;

	words = NULL;
	i = 0;
	while (cmd->argv[i])
	{
		if (!collect_words(&words, cmd->argv[i], shell))
		{
			ft_lstclear(&words, free);
			return (0);
		}
		i++;
	}
	new_argv = list_to_argv(words);
	if (!new_argv)
	{
		ft_lstclear(&words, free);
		return (0);
	}
	free_array(cmd->argv);
	ft_lstclear(&words, noop_free);
	cmd->argv = new_argv;
	return (1);
}

static int	expand_redirs(t_redir *redir, t_shell *shell)
{
	char	*expanded;

	while (redir)
	{
		if (redir->type != T_HEREDOC)
		{
			expanded = expand_arg(redir->target, shell, 0);
			if (!expanded)
				return (0);
			free(redir->target);
			redir->target = expanded;
		}
		redir = redir->next;
	}
	return (1);
}

int	expand_args(t_cmd *cmds, t_shell *shell)
{
	while (cmds)
	{
		if (!expand_redirs(cmds->redirs, shell))
			return (0);
		if (!expand_argv(cmds, shell))
			return (0);
		cmds = cmds->next;
	}
	return (1);
}
