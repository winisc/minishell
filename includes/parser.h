/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

/*
** Redirecionamento de um comando (lista encadeada).
** type reaproveita t_token_type: T_REDIR_IN, T_REDIR_OUT, T_APPEND, T_HEREDOC.
*/
typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	int				fd;
	struct s_redir	*next;
}	t_redir;

/*
** Comando único de um pipeline (lista encadeada por pipes).
** argv termina em NULL; redirs pode ser NULL.
*/
typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*parser(t_token *tokens, t_shell *shell);

int		is_redir(t_token_type type);
int		syntax_valid(t_token *tokens);

t_cmd	*cmd_new(int argc);
void	cmd_add_back(t_cmd **head, t_cmd *new);
void	cmd_free(t_cmd *cmd);
void	cmd_clear(t_cmd *head);

int		add_redir(t_cmd *cmd, t_token_type type, char *target);
void	redir_add_back(t_redir **head, t_redir *new);
void	redir_clear(t_redir *head);

#endif
