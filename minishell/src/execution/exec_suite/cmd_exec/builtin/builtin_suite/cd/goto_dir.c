/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goto_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:05:35 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/10 16:59:06 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	set_oldpwd(char **env, char *pwd)
{
	int		i;
	char	*oldpwd;

	i = -1;
	while (env[++i])
		if (ft_strncmp("OLDPWD=", env[i], 7) == 0)
			break ;
	if (env[i] == NULL)
		return (0);
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

static int	set_pwd(char **env)
{
	int		i;
	char	*new_pwd;
	char	*pwd;

	i = -1;
	while (env[++i])
		if (ft_strncmp("PWD=", env[i], 4) == 0)
			break ;
	if (env[i] == NULL)
		return (0);
	pwd = get_cwd(env);
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

/*
* Goal: Change the current woring dirrectory to the given dirrectory.
*		Update the values of PWD and OLDPWD
*
* Return: 0 on success, 1 on failure.
*/
int	goto_dir(char *dir, char **env)
{
	int			result;
	char		*pwd;

	pwd = get_cwd(env);
	if (!pwd)
		return (1);
	if (*dir)
	{
		result = chdir(dir);
		if (result)
		{
			free(pwd);
			if (access(dir, F_OK) == 0 && access(dir, R_OK | X_OK))
				ft_printf_fd(2, "%s: cd: %s: %s\n", NAME, dir, ERR_NO_PERM);
			else
				ft_printf_fd(2, "%s: cd: %s: %s\n", NAME, dir, ERR_NO_FILE);
			return (1);
		}
	}
	result = set_oldpwd(env, pwd);
	free(pwd);
	if (result)
		return (result);
	result = set_pwd(env);
	return (result);
}
