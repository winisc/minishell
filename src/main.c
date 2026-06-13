/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 18:31:49 by wsilveir          #+#    #+#             */
/*   Updated: 2026/06/13 01:58:34 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	handle_signal_status(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->last_status = 130;
		g_signal = 0;
	}
}

static int	shell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		set_signals_interactive();
		input = readline("minishell$ ");
		handle_signal_status(shell);
		if (!input)
		{
			rl_clear_history();
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (process_input(input, shell) == EXIT_REQUESTED)
			break ;
		free(input);
	}
	free(input);
	return (shell->last_status);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	int		status;

	(void)ac;
	(void)av;
	shell.env = env_init(envp);
	shell.last_status = 0;
	shell.exit_flag = 0;
	status = shell_loop(&shell);
	env_destroy(shell.env);
	return (status);
}
