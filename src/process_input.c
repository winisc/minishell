/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:25:03 by wini              #+#    #+#             */
/*   Updated: 2026/04/22 13:25:03 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Processa entrada do usuário através do pipeline completo */
int	process_input(char *input)
{
	/* TODO: Lexer - Tokenizar entrada */
	/* t_token *tokens = lexer(input); */

	/* TODO: Parser - Construir AST */
	/* t_ast *ast = parser(tokens); */

	/* TODO: Executor - Executar comandos */
	/* execute(ast); */

	/* TODO: Liberar recursos */
	/* free_tokens(tokens); */
	/* free_ast(ast); */

	/* TODO: Detectar comando "exit" */
	/* if (check_exit_command(input)) */
	/*     return (EXIT_REQUESTED); */

	return (CONTINUE_SHELL);
}
