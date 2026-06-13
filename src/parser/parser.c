/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_words(t_token *t)
{
	int	n;

	n = 0;
	while (t && t->type != T_PIPE)
	{
		if (is_redir(t->type))
			t = t->next;
		else
			n++;
		t = t->next;
	}
	return (n);
}

static int	fill_command(t_cmd *cmd, t_token **tokens)
{
	t_token	*t;
	int		i;

	t = *tokens;
	i = 0;
	while (t && t->type != T_PIPE)
	{
		if (is_redir(t->type))
		{
			if (!add_redir(cmd, t->type, t->next->value))
				return (0);
			t = t->next->next;
		}
		else
		{
			cmd->argv[i] = ft_strdup(t->value);
			if (!cmd->argv[i++])
				return (0);
			t = t->next;
		}
	}
	*tokens = t;
	return (1);
}

static t_cmd	*build_one_command(t_token **tokens)
{
	t_cmd	*cmd;

	cmd = cmd_new(count_words(*tokens));
	if (!cmd)
		return (NULL);
	if (!fill_command(cmd, tokens))
	{
		cmd_free(cmd);
		return (NULL);
	}
	return (cmd);
}

static t_cmd	*build_commands(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*cmd;

	head = NULL;
	while (tokens)
	{
		cmd = build_one_command(&tokens);
		if (!cmd)
		{
			cmd_clear(head);
			return (NULL);
		}
		cmd_add_back(&head, cmd);
		if (tokens && tokens->type == T_PIPE)
			tokens = tokens->next;
	}
	return (head);
}

t_cmd	*parser(t_token *tokens, t_shell *shell)
{
	if (!syntax_valid(tokens))
	{
		shell->last_status = 2;
		return (NULL);
	}
	return (build_commands(tokens));
}
