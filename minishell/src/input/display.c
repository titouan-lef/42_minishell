/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/06 17:06:36 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
* Goal: Add collor patern to the given string.
*
* Return: Ths colored string, NULL is error malloc
*
* Warning: pwd must not be null.
*/
static char	*rebase_pwd(char *pwd, char **env)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	if (!pwd)
		return (NULL);
	while (env[i])
		if (ft_strncmp("HOME=", env[i++], 5) == 0)
			break ;
	if (env[i--] != NULL)
	{
		if (ft_strncmp(pwd, env[i] + 5, ft_strlen(env[i] + 5)) == 0)
		{
			result = ft_strjoin("~", pwd + ft_strlen(env[i] + 5));
			free(pwd);
			return (result);
		}
		return (pwd);
	}
	return (pwd);
}

/*
* Goal: Add collor patern to the given string.
*
* Return: Ths colored string, NULL is error malloc
*
* Warning: pwd must not be null.
*/
static char	*color_pwd(char *pwd)
{
	static unsigned char	color = 28;
	char					*new_pwd;
	char					*tmp;

	tmp = ft_itoa(color);
	new_pwd = ft_strjoin("\1\e[38;5;", tmp);
	free(tmp);
	tmp = ft_strjoin(new_pwd, "m\2");
	free (new_pwd);
	new_pwd = ft_strjoin(tmp, pwd);
	free(tmp);
	free(pwd);
	tmp = ft_strjoin(new_pwd, "\1\e[0m\2");
	free(new_pwd);
	color++;
	return (tmp);
}

/*
* Goal: Generate the prompt with the current directory.
*
* Return: The prompt, NULL is error malloc
*
* Warning: env must not be null.
*/
char	*get_prompt(char **env)
{
	char	*pwd;
	char	*prompt;
	char	*tmp;

	pwd = get_cwd(env);
	pwd = rebase_pwd(pwd, env);
	pwd = color_pwd(pwd);
	prompt = ft_strjoin(NAME, ":");
	tmp = ft_strjoin(prompt, pwd);
	free(pwd);
	free(prompt);
	prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	if (!prompt)
	{
		prompt = ft_strdup("minishell$ ");
		if (!prompt)
			ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (prompt);
	}
	return (prompt);
}
