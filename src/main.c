/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 18:31:49 by wsilveir          #+#    #+#             */
/*   Updated: 2026/04/22 13:24:46 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;

	init_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			rl_clear_history();
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (process_input(input) == EXIT_REQUESTED)
		{
			free(input);
			break ;
		}
		free(input);
	}
	return (0);
}
