/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 19:27:31 by wini              #+#    #+#             */
/*   Updated: 2026/06/08 23:48:25 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*read_operator(char *input, int *i)
{
	if (input[*i] == '|')
	{
		(*i)++;
		return (token_new(T_PIPE, "|"));
	}
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		(*i) += 2;
		return (token_new(T_APPEND, ">>"));
	}
	if (input[*i] == '>')
	{
		(*i)++;
		return (token_new(T_REDIR_OUT, ">"));
	}
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		(*i) += 2;
		return (token_new(T_HEREDOC, "<<"));
	}
	(*i)++;
	return (token_new(T_REDIR_IN, "<"));
}

static t_token	*read_word(char *input, int *i)
{
	int		start;
	char	quote;
	char	*value;
	t_token	*tok;

	start = *i;
	while (input[*i] && !is_whitespace(input[*i]) && !is_operator(input[*i]))
	{
		if (is_quote(input[*i]))
		{
			quote = input[(*i)++];
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (input[*i])
				(*i)++;
		}
		else
			(*i)++;
	}
	value = ft_substr(input, start, *i - start);
	if (!value)
		return (NULL);
	tok = token_new(T_WORD, value);
	free(value);
	return (tok);
}

static int	push_token(t_token **head, char *input, int *i)
{
	t_token	*tok;

	if (is_operator(input[*i]))
		tok = read_operator(input, i);
	else
		tok = read_word(input, i);
	if (!tok)
		return (0);
	token_add_back(head, tok);
	return (1);
}

t_token	*lexer(char *input)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (is_whitespace(input[i]))
			i++;
		else if (!push_token(&head, input, &i))
		{
			free_tokens(head);
			return (NULL);
		}
	}
	return (head);
}
