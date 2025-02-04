/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:57:15 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/04 17:00:02 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	import_var(char *var, int size, char ***env, int local)
{
	int		j;
	char	*tmp;

	j = 1;
	while ((*env)[j])
	{
		if (!ft_strncmp(var, (*env)[j], size)
			&& (!(*env)[j][size] || (*env)[j][size] == '='))
			break;
		j++;
	}
	if (!(*env)[j])
		*env = append_to_tab(*env, var);
	else if (local)
	{
		tmp = ft_strdup(var);
		if (!tmp)
		{
			ft_printf_fd(2, "%s:, %s\n", NAME, ERR_MALLOC);
			return (1);
		}
		free((*env)[j]);
		(*env)[j] = tmp;
	}
	return (0);
}

static int	length_valid_name(char *var)
{
	int	size;

	size = 0;
	while (var[size] && var[size] != '=')
	{
		if (!ft_isalnum(var[size]) && var[size] != '_')
		{
			ft_printf_fd(2, "%s: export: %s: %s\n", NAME, var, ERR_EXP);
			return (-1);
		}
		size++;
	}
	return (size);
}

int	print_export(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		ft_putstr("declare -x ");
		while (env[i][j] && env[i][j] != '=')
			ft_putchar(env[i][j++]);
		if (env[i][j])
			ft_printf("=\"%s\"\n", env[i] + j + 1);
		else
			ft_putchar('\n');
		i++;
	}
	return (0);
}

int	export(char **cmd, char ***env_local, char ***env_export)
{
	int	i;
	int	size;
	int	result;

	i = 1;
	while (cmd[i])
	{
		size = length_valid_name(cmd[i]);
		if (size != -1)
		{
			if (cmd[i][size])
			{
				result = import_var(cmd[i], size, env_local, 1);
				result = import_var(cmd[i], size, env_export, 1);
			}
			else
				result = import_var(cmd[i], size, env_export, 0);
		}
		i++;
	}
	if (i == 1)
		result = print_export(*env_export);
	return (result);
}
