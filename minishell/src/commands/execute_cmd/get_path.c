/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:49:12 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/20 16:19:37 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_paths_in_env(char **env)
{
	int		i;
	char	*path;
	char	**paths_tab;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path = env[i] + 5;
		i++;
	}
	if (!path)
	{
		ft_printf_fd(2, "%s: no PATH in the current environement", NAME);
		return (NULL);
	}
	paths_tab = ft_split(path, ':');
	if (!paths_tab)
		ft_printf_fd(2, "%s: %s", NAME, MALLOC);
	return (paths_tab);
}

static int	add_path_and_access(char *dir, char *cmd, char **path)
{
	char	*temp;

	temp = ft_strjoin(dir, "/");
	if (!temp)
	{
		ft_printf_fd(2, "%s: %s", NAME, MALLOC);
		return (1);
	}
	*path = ft_strjoin(temp, cmd);
	free(temp);
	if (!*path)
	{
		ft_printf_fd(2, "%s: %s", NAME, MALLOC);
		return (1);
	}
	if (access(*path, F_OK | X_OK) != 0)
	{
		free(*path);
		*path = NULL;
	}
	return (0);
}

static int	access_path_cmd(char *cmd_name, char **path)
{
	if (access(cmd_name, F_OK | X_OK) == 0)
	{
		*path = ft_strdup(cmd_name);
		if (*path)
			return (0);
		ft_printf_fd(2, "%s: %s", NAME, MALLOC);
		return (1);
	}
	ft_printf_fd(2, "%s: %s: %s", NAME, cmd_name, NO_FILE);
	return (127);
}

int	get_path(char **path, char *cmd_name, char **env)
{
	char	**paths_tab;
	int		i;
	int		result;

	if (ft_strchr(cmd_name, '/'))
	{
		result = access_path_cmd(cmd_name, path);
		return (result);
	}
	paths_tab = find_paths_in_env(env);
	if (!path)
		return (1);
	i = 0;
	while (paths_tab && paths_tab[i])
	{
		result = add_path_and_access(paths_tab[i++], cmd_name, path);
		if (result || *path)
		{
			ft_clean_matrix((void **)paths_tab);
			return (result);
		}
	}
	if (paths_tab)
		ft_clean_matrix((void **)paths_tab);
	return (1);
}
