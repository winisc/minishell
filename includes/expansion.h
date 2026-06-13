/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "parser.h"

/*
** IFS_SEP marca, dentro de uma string expandida, os limites onde o word
** splitting deve ocorrer (espaços vindos de variaveis NAO entre aspas).
*/
# define IFS_SEP '\037'

typedef struct s_exp
{
	t_shell	*shell;
	int		quoted;
	int		split;
}	t_exp;

int		expand_args(t_cmd *cmds, t_shell *shell);
char	*expand_arg(char *arg, t_shell *shell, int split);

char	*append_char(char *res, char c);
char	*append_single(char *res, char *arg, int *i);
char	*append_double(char *res, char *arg, int *i, t_exp *exp);
char	*append_dollar(char *res, char *arg, int *i, t_exp *exp);
char	*append_split(char *res, char *value);

char	*append_free(char *dst, char *src);
int		is_name_start(char c);
int		is_name_char(char c);
int		has_quote_char(char *str);

int		collect_words(t_list **words, char *arg, t_shell *shell);
char	**list_to_argv(t_list *words);
void	noop_free(void *content);

#endif
