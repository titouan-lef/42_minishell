/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:05:35 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/28 19:16:01 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int set_oldpwd(char **env, char *pwd)
{
	int		i;
	char	*oldpwd;

	i = 0;
	while (env[i])
		if (ft_strncmp("OLDPWD=", env[i++], 7) == 0)
			break ;
	if (env[i] == NULL)
		return (0);
	i--;
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	if (!oldpwd)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (1);
	}
	free(env[i]);
	env[i] = oldpwd;
	return (0);
}

static int set_pwd(char **env)
{
	int		i;
	char	*new_pwd;
	char	*pwd;

	i = 0;
	while (env[i])
		if (ft_strncmp("PWD=", env[i++], 4) == 0)
			break ;
	if (env[i] == NULL)
		return (0);
	i--;
	pwd = get_cdw(env);
	if (!pwd)
		return (1);
	new_pwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!new_pwd)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (1);
	}
	free(env[i]);
	env[i] = new_pwd;
	return (0);
}

static int	goto_dir(char *dir, char **env)
{
	int		result;
	char	*pwd;

	pwd = get_cdw(env);
	if (!pwd)
		return (1);
	result = chdir(dir);
	if (result)
	{
		free(pwd);
		ft_printf_fd(2, "%s: cd: %s: %s\n", NAME, dir, ERR_NO_FILE);
		return (1);
	}
	set_oldpwd(env, pwd);
	free(pwd);
	set_pwd(env);
	return (0);
}

static int goto_home(char **env)
{
	int		i;
	int		result;
	char	*home;

	i = 0;
	while (env[i])
		if (ft_strncmp("HOME=", env[i++], 5) == 0)
			break ;
	if (env[i] == NULL)
	{
		ft_printf_fd(2, "%s: cd: HOME not set\n", NAME);
		return (1);
	}
	--i;
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

	i = 0;
	while (env[i])
		if (ft_strncmp("OLDPWD=", env[i++], 7) == 0)
			break ;
	i--;
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
		printf("%s\n", oldpwd);
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

	if (cmd[1] == NULL || ft_strncmp("~", cmd[1], 2) == 0)
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
