/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:01:24 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/10 15:09:27 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
* Goal: Found the value of the vairalbe 'name'.
*
* Return: The curent wordking dirrectory path, NULL if error.
*
* Warning: The returned value must be freed.
*/
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

/*
* Goal: Found the current working dirrectory.
*		If getcwd fails, return the value of PWD.
*
* Return: The curent wordking dirrectory path, NULL if error.
*/
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
		if (!env)
			return (NULL);
		pwd = get_from_env(env, "PWD");
	}
	return (pwd);
}
