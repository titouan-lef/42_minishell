/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:05:35 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/06 16:15:35 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "cmd_exec.h"

static int	goto_home(char **env)
{
	int		i;
	int		result;
	char	*home;

	i = -1;
	while (env[++i])
		if (ft_strncmp("HOME=", env[i], 5) == 0)
			break ;
	if (env[i] == NULL)
	{
		ft_printf_fd(2, "%s: cd: HOME not set\n", NAME);
		return (1);
	}
	home = ft_strdup(env[i] + 5);
	if (!home)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (1);
	}
	result = goto_dir(home, env);
	free(home);
	return (result);
}

static int	goback(char **env)
{
	int		result;
	int		i;
	char	*oldpwd;

	i = -1;
	while (env[++i])
		if (ft_strncmp("OLDPWD=", env[i], 7) == 0)
			break ;
	if (env[i] == NULL)
	{
		ft_printf_fd(2, "%s: cd: OLDPWD not set\n", NAME);
		return (1);
	}
	oldpwd = ft_strdup(env[i] + 7);
	if (!oldpwd)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (1);
	}
	result = goto_dir(oldpwd, env);
	if (result == 0)
		ft_printf("%s\n", oldpwd);
	free(oldpwd);
	return (result);
}

/*
* Goal: Equivalent of the pwd cd.
*
* Return: 1 in case of error, 0 if none.
*
* Warning: env must not be null.
*/
int	cd(char **cmd, char **env)
{
	int			result;
	struct stat	infos;

	if (cmd[1] == NULL || ft_strncmp("--", cmd[1], 3) == 0)
		result = goto_home(env);
	else if (cmd[2] != NULL)
	{
		ft_printf_fd(2, "%s: cd: too many arguments\n", NAME);
		result = 1;
	}
	else if (ft_strncmp("-", cmd[1], 2) == 0)
		result = goback(env);
	else if (stat(cmd[1], &infos) == 0 && !S_ISDIR(infos.st_mode))
	{
		ft_printf_fd(2, "%s: cd: %s: Not a directory\n", NAME, cmd[1]);
		result = 1;
	}
	else
		result = goto_dir(cmd[1], env);
	return (result);
}
