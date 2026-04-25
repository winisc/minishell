/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 18:33:24 by wsilveir          #+#    #+#             */
/*   Updated: 2026/04/25 17:14:25 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define EXIT_REQUESTED 1
# define CONTINUE_SHELL 0

/* Inicializa os handlers de sinais */
void	init_signals(void);
/* Processa entrada do usuário: lexer → parser → execution */
int		process_input(char *input);
/**/
void	lexer(char *input);
#endif
