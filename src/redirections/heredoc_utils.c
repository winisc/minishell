/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_delim(char *line, char *delim)
{
	size_t	len;

	len = ft_strlen(delim);
	return (ft_strncmp(line, delim, len + 1) == 0);
}

char	*strip_quotes(char *s)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			i++;
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

void	heredoc_child(int *pfd, char *delim, t_cmd *head, t_shell *shell)
{
	char	*line;

	close(pfd[0]);
	set_signals_default();
	line = readline("> ");
	while (line && !is_delim(line, delim))
	{
		ft_putendl_fd(line, pfd[1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	free(delim);
	close(pfd[1]);
	rl_clear_history();
	cmd_clear(head);
	env_destroy(shell->env);
	exit(0);
}
