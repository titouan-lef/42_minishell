/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:21:18 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/02 17:09:37 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_from_env(char **env, char *name)
{
	char	*pwd;
	int		i;
	int		length;

	length = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(name, env[i], length) == 0 && env[i][length] == '=')
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	pwd = ft_strdup(env[i] + length + 1);
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
		pwd = get_from_env(env, "PWD");
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
