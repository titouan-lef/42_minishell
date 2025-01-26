/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:49:12 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/26 15:03:50 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Goal: Find all the possible paths where to execute the dommand.
*
* Return: a tab with all the paths, NULL if error.
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
	{
		ft_printf_fd(2, "%s: no PATH in the current environement", NAME);
		return (NULL);
	}
	paths_tab = ft_split(path, ':');
	if (!paths_tab)
		ft_printf_fd(2, "%s: %s", NAME, ERR_MALLOC);
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
		ft_printf_fd(2, "%s: %s", NAME, ERR_MALLOC);
		return (1);
	}
	*path = ft_strjoin(temp, cmd);
	free(temp);
	if (!*path)
	{
		ft_printf_fd(2, "%s: %s", NAME, ERR_MALLOC);
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
	if (access(cmd_name, F_OK | X_OK) == 0)
	{
		*path = ft_strdup(cmd_name);
		if (*path)
			return (0);
		ft_printf_fd(2, "%s: %s", NAME, ERR_MALLOC);
		return (1);
	}
	ft_printf_fd(2, "%s: %s: %s", NAME, cmd_name, ERR_NO_FILE);
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

	if (ft_strchr(cmd_name, '/'))
	{
		result = access_path_cmd(cmd_name, path);
		return (result);
	}
	paths_tab = find_paths_in_env(env);
	if (!paths_tab)
		return (1);
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
	ft_printf_fd(2, "%s: %s\n", cmd_name, ERR_NO_CMD);
	ft_clean_matrix((void **)paths_tab);
	return (127);
}
