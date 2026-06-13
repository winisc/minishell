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
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define EXIT_REQUESTED 1
# define CONTINUE_SHELL 0

extern volatile sig_atomic_t	g_signal;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	int		last_status;
	int		exit_flag;
}	t_shell;

void	set_signals_interactive(void);
void	set_signals_exec(void);
void	set_signals_default(void);
int		process_input(char *input, t_shell *shell);

t_env	*env_init(char **envp);
void	env_destroy(t_env *head);
void	env_add_back(t_env **head, t_env *new);
char	*env_get(t_env *head, char *key);
int		env_set(t_env **head, char *key, char *value);
int		env_unset(t_env **head, char *key);
char	**env_to_array(t_env *head);

void	free_array(char **arr);
int		array_size(char **arr);
void	error_msg(char *ctx, char *arg, char *msg);

#endif
