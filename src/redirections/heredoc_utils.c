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
#include "expansion.h"

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

static void	write_heredoc_line(int fd, char *line, int expand, t_shell *shell)
{
	char	*expanded;

	if (expand)
	{
		expanded = expand_arg(line, shell, 0);
		ft_putendl_fd(expanded, fd);
		free(expanded);
	}
	else
		ft_putendl_fd(line, fd);
	free(line);
}

void	heredoc_child(int *pfd, char *delim, t_cmd *head, t_shell *shell)
{
	char	*line;
	char	*clean;
	int		expand;

	close(pfd[0]);
	expand = !has_quote_char(delim);
	clean = strip_quotes(delim);
	set_signals_default();
	signal(SIGQUIT, SIG_IGN);
	line = readline("> ");
	while (line && !is_delim(line, clean))
	{
		write_heredoc_line(pfd[1], line, expand, shell);
		line = readline("> ");
	}
	free(line);
	free(clean);
	close(pfd[1]);
	rl_clear_history();
	cmd_clear(head);
	env_destroy(shell->env);
	exit(0);
}
