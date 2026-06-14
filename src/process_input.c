/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:25:03 by wini              #+#    #+#             */
/*   Updated: 2026/06/13 17:26:43 by wsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "execution.h"

int	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (has_unclosed_quotes(input))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		shell->last_status = 2;
		return (CONTINUE_SHELL);
	}
	tokens = lexer(input);
	cmds = parser(tokens, shell);
	free_tokens(tokens);
	if (cmds && expand_args(cmds, shell))
		execute(cmds, shell);
	cmd_clear(cmds);
	if (shell->exit_flag)
		return (EXIT_REQUESTED);
	return (CONTINUE_SHELL);
}
