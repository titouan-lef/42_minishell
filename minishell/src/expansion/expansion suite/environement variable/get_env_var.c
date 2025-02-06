/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/06 15:09:00 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/*
* Goal: Find the value of the 'name' env var int the env_local.
*
* Return: The value of the env var.
*
* Warning: name and env_local must not be null.
*/
static char	*get_value(char *name, char **env_local)
{
	int		name_length;

	name_length = 0;
	while (ft_isalnum(*(name + name_length)) || *(name + name_length) == '_')
		name_length++;
	if (!name_length)
		return ("$");
	while (*env_local && name_length)
	{
		if (ft_strncmp(name, *env_local, name_length) == 0
			&& *(*env_local + name_length) == '=')
			return (*env_local + name_length + 1);
		env_local++;
	}
	return (NULL);
}

/*
* Goal: Find the value of the 'name' env var int the env
*		and quote the quotes.
*
* Return: The quoted value of the env var.
*
* Warning: name and env must not be null.
*/
char	*get_quoted_value(char *name, char **env)
{
	int		i;
	char	*value;
	char	*quoted_value;

	value = get_value(name, env);
	if (!value)
		return (NULL);
	quoted_value = ft_calloc(value_length_quoted(value) + 1, sizeof(char));
	if (!quoted_value)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (NULL);
	}
	i = 0;
	while (*value)
	{
		quote_value(value, quoted_value, &i);
		value++;
	}
	return (quoted_value);
}
