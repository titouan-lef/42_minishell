/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:55:17 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/04 16:02:37 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"

static int	builtin_choice(char **cmd, t_data *data, int is_piped)
{
	int	result;

	result = -1;
	if (!ft_strcmp(cmd[0], "echo"))
		result = echo(cmd);
	else if (!ft_strcmp(cmd[0], "cd"))
		result = cd(cmd, data->env);
	else if (!ft_strcmp(cmd[0], "pwd"))
		result = pwd(data->env);
	else if (!ft_strcmp(cmd[0], "export"))
		result = export(cmd, &data->env, &data->env_export);
	else if (!ft_strcmp(cmd[0], "unset"))
	{
		result = unset(cmd, &data->env);
		result = unset(cmd, &data->env_export);
	}
	else if (!ft_strcmp(cmd[0], "env"))
		result = env(cmd, data->env);
	else
		result = my_exit(cmd, data, is_piped);
	return (result);
}

/*
* Goal: Launch the corresponding builtins command.
*
* Return: O if no error, or the error code corresponding.
*
* Warning: cmd and data must not be null.
*/
int	builtin_manager(char **cmd, char **redir, t_data *data, int is_piped)
{
	int	result;
	int	result2;

	if (!is_piped)
	{
		result = dup_data_std(data);
		if (result)
			return (result);
	}
	result = redir_manager(redir, data->lst);
	if (result)
	{
		if (!is_piped)
			close_data_std(data);
		return (result);
	}
	result = builtin_choice(cmd, data, is_piped);
	data->last_exit = result;
	if (!is_piped)
		result2 = dup2_data_std(data);
	close_data_std(data);
	if (!is_piped && result2)
		return (result2);
	return (result);
}
