/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redir(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_APPEND || type == T_HEREDOC);
}

static int	syntax_error(char *near)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(near, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

static int	redir_ok(t_token *redir)
{
	if (!redir->next)
		return (syntax_error("newline"));
	if (redir->next->type != T_WORD)
		return (syntax_error(redir->next->value));
	return (1);
}

static int	pipe_ok(t_token *pipe)
{
	if (!pipe->next)
		return (syntax_error("newline"));
	if (pipe->next->type == T_PIPE)
		return (syntax_error("|"));
	return (1);
}

int	syntax_valid(t_token *tokens)
{
	if (tokens && tokens->type == T_PIPE)
		return (syntax_error("|"));
	while (tokens)
	{
		if (is_redir(tokens->type) && !redir_ok(tokens))
			return (0);
		if (tokens->type == T_PIPE && !pipe_ok(tokens))
			return (0);
		tokens = tokens->next;
	}
	return (1);
}
