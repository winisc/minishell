/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/09 00:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*try_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full)
		return (NULL);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

static char	*search_dirs(char **dirs, char *cmd)
{
	char	*full;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full = try_path(dirs[i], cmd);
		if (full)
			return (full);
		i++;
	}
	return (NULL);
}

char	*resolve_path(char *cmd, t_env *env)
{
	char	**dirs;
	char	*full;
	char	*path;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = env_get(env, "PATH");
	if (!path || !path[0])
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	full = search_dirs(dirs, cmd);
	free_array(dirs);
	return (full);
}
