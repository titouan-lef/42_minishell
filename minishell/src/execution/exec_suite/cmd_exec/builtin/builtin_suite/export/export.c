/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:57:15 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/13 20:13:49 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	replace_var(char **var, char *new_var, int size)
{
	char	*tmp;

	if (new_var[size] == '+')
		tmp = ft_strjoin(*var, new_var + size + 2);
	else
		tmp = ft_strdup(new_var);
	if (!tmp)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (1);
	}
	free(*var);
	*var = tmp;
	return (0);
}

static int	add_var(char *var, int size, char ***env)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	if (var[size] == '+')
	{
		tmp = ft_strndup(var, size);
		if (!tmp)
			return (1);
		tmp2 = ft_strjoin(tmp, var + size + 1);
		free(tmp);
		if (!tmp2)
			return (1);
		var = tmp2;
	}
	*env = append_to_tab(*env, var);
	free(tmp2);
	if (!*env)
		return (1);
	return (0);
}

static int	import_var(char *var, int size, char ***env, int local)
{
	int	j;

	j = 0;
	while ((*env)[j])
	{
		if (!ft_strncmp(var, (*env)[j], size) && (!(*env)[j][size]
			|| (*env)[j][size] == '=' || (*env)[j][size] == '+'))
			break ;
		j++;
	}
	if (!(*env)[j])
	{
		if (add_var(var, size, env))
		{
			ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
			return (1);
		}
	}
	else if (local)
		if (replace_var(&(*env)[j], var, size))
			return (1);
	return (0);
}

static int	length_valid_name(char *var, int *result)
{
	int	size;

	size = 0;
	if (!ft_isalpha(var[size]) && var[size] != '_')
	{
		ft_printf_fd(2, "%s: export: `%s': %s\n", NAME, var, ERR_EXP);
		*result = 1;
		return (-1);
	}
	size = 0;
	while (var[size] && var[size] != '=')
	{
		if (!ft_isalnum(var[size]) && var[size] != '_')
		{
			if (var[size] == '+' && var[size + 1] == '=')
				return (size);
			ft_printf_fd(2, "%s: export: `%s': %s\n", NAME, var, ERR_EXP);
			*result = 1;
			return (-1);
		}
		size++;
	}
	return (size);
}

/*
* Goal: Add the givens varivalies given in cmd, in the environement.
*		Add only is env_exprot if no value is preciced.
*		Prints the env_export if not argument in given in cmd.
*
* Return: 1 if at least one of the variable name is invalid, 0 if not.
*/
int	export(char **cmd, char ***env_local, char ***env_export)
{
	int	i;
	int	size;
	int	result;

	result = 0;
	i = 0;
	while (cmd[++i])
	{
		size = length_valid_name(cmd[i], &result);
		if (size != -1)
		{
			if (cmd[i][size])
			{
				if (import_var(cmd[i], size, env_local, 1))
					return (1);
				if (import_var(cmd[i], size, env_export, 1))
					return (1);
			}
			else if (import_var(cmd[i], size, env_export, 0))
				return (1);
		}
	}
	if (i == 1)
		print_export(*env_export);
	return (result);
}
