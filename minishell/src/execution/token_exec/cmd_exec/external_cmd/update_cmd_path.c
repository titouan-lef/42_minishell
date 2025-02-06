/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:49:12 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/06 15:59:04 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "cmd_exec.h"

/*
* Goal: Find all the possible paths where to execute the dommand.
*
* Return: A tab with all the paths, NULL if PATH is not set
*			NULL in case of malloc error, it may print 2 error msg in the end.
*
* Warning: env must not be null.
*/
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
		return (NULL);
	paths_tab = ft_split(path, ':');
	if (!paths_tab)
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
	return (paths_tab);
}

/*
* Goal: Try to acces to the command .
*
* Return: 1 if error, 0 if not
*		(path is set to null if can't access to the command).
*
* Warning: dir, cmd and path must not be null.
*/
static int	add_path_and_access(char *dir, char *cmd, char **path)
{
	char	*temp;

	temp = ft_strjoin(dir, "/");
	if (!temp)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (1);
	}
	*path = ft_strjoin(temp, cmd);
	free(temp);
	if (!*path)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (1);
	}
	if (access(*path, F_OK | X_OK) != 0)
	{
		free(*path);
		*path = NULL;
	}
	return (0);
}

/*
* Goal: Try to access the command.
*
* Return: 0 if the command is accesible, or the error code if error.
*
* Warning: cmd_name and path must not be null.
*/
static int	access_path_cmd(char *cmd_name, char **path)
{
	struct stat	infos;

	if (stat(cmd_name, &infos) == 0 && S_ISDIR(infos.st_mode))
	{
		ft_printf_fd(2, "%s: %s: Is a directory\n", NAME, cmd_name);
		return (126);
	}
	if (access(cmd_name, F_OK | X_OK) == 0)
	{
		*path = ft_strdup(cmd_name);
		if (*path)
			return (0);
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (1);
	}
	if (access(cmd_name, F_OK) == 0 && access(cmd_name, X_OK))
	{
		ft_printf_fd(2, "%s: %s: %s\n", NAME, cmd_name, ERR_NO_PERM);
		return (126);
	}
	ft_printf_fd(2, "%s: %s: %s\n", NAME, cmd_name, ERR_NO_FILE);
	return (127);
}

/*
* Goal: Find were to execute the command.
*
* Return: 0 if the command is accesible, or the error code if error.
*
* Warning: path, cmd_name and env must not be null.
*/
int	update_cmd_path(char **path, char *cmd_name, char **env)
{
	char	**paths_tab;
	int		i;
	int		result;

	paths_tab = find_paths_in_env(env);
	if (ft_strchr(cmd_name, '/') || !paths_tab)
	{
		result = access_path_cmd(cmd_name, path);
		if (paths_tab)
			ft_clean_matrix((void **)paths_tab);
		return (result);
	}
	i = 0;
	while (paths_tab[i])
	{
		result = add_path_and_access(paths_tab[i++], cmd_name, path);
		if (result || *path)
		{
			ft_clean_matrix((void **)paths_tab);
			return (result);
		}
	}
	ft_printf_fd(2, "%s: %s: %s\n", NAME, cmd_name, ERR_NO_CMD);
	ft_clean_matrix((void **)paths_tab);
	return (127);
}
