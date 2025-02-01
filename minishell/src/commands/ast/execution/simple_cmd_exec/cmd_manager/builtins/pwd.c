/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:21:18 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/01 17:46:58 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_pwd_from_env(char **env)
{
	char	*pwd;
	int		i;

	i = 0;
	while (env[i])
		if (ft_strncmp("PWD=", env[i++], 4) == 0)
			break ;
	if (env[i] == NULL)
		return (NULL);
	i--;
	pwd = ft_strdup(env[i] + 4);
	if (!pwd)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (NULL);
	}
	return (pwd);
}

char	*get_cwd(char **env)
{
	char	*pwd;

	pwd = (char *)ft_calloc(sizeof(char), PATH_MAX);
	if (!pwd)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (NULL);
	}
	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		free(pwd);
		pwd = get_pwd_from_env(env);
	}
	return (pwd);
}

/*
* Goal: Equivalent of the pwd command.
*
* Return: Nothing.
*
* Warning: None.
*/
int	pwd(char **env)
{
	char	*pwd;

	pwd = get_cwd(env);
	if (pwd == NULL)
		return (1);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}
