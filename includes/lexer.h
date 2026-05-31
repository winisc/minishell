/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 19:04:29 by wini              #+#    #+#             */
/*   Updated: 2026/04/23 19:19:23 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
/*
** Tipos de tokens reconhecidos pelo lexer
*/
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

/*
** Estrutura de token (lista encadeada)
*/
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

t_token	*token_new(t_token_type type, char *value);
void	token_add_back(t_token **head, t_token *new);
void	free_tokens(t_token *head);

int		is_whitespace(char c);
int		is_operator(char c);
int		is_quote(char c);

t_token	*lexer(char *input);

#endif