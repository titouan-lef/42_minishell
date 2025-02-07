/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:55:17 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/07 19:15:01 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	dup_data_std(int *std)
{
	std[0] = dup(STDIN_FILENO);
	if (std[0] < 0)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_DUP);
		std[1] = -1;
		std[2] = -1;
		return (1);
	}
	std[1] = dup(STDOUT_FILENO);
	if (std[1] < 0)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_DUP);
		std[2] = -1;
		return (1);
	}
	std[2] = dup(STDERR_FILENO);
	if (std[2] < 0)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_DUP);
		return (1);
	}
	return (0);
}

static int	dup2_data_std(int *std)
{
	int	result;
	int	is_error;

	is_error = 0;
	result = dup2(std[0], STDIN_FILENO);
	if (result < 0)
		is_error = 1;
	result = dup2(std[1], STDOUT_FILENO);
	if (result < 0)
		is_error = 1;
	result = dup2(std[2], STDERR_FILENO);
	if (result < 0)
		is_error = 1;
	if (is_error)
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_DUP2);
	return (is_error);
}

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
		if (!result)
			result = unset(cmd, &data->env_export);
	}
	else if (!ft_strcmp(cmd[0], "env"))
		result = env(cmd, data->env);
	else
		result = my_exit(cmd, data, is_piped);
	return (result);
}

static void	close_data_std(int *std)
{
	if (std[0] != -1)
		close(std[0]);
	if (std[1] != -1)
		close(std[1]);
	if (std[2] != -1)
		close(std[2]);
	std[0] = -1;
	std[1] = -1;
	std[2] = -1;
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
	int	std[3];

	if (!is_piped)
	{
		if (dup_data_std(std))
			return (1);
	}
	result = redir_manager(redir, data->lst);
	if (result)
	{
		if (!is_piped)
			close_data_std(std);
		return (result);
	}
	result = builtin_choice(cmd, data, is_piped);
	if (!is_piped)
	{
		result2 = dup2_data_std(std);
		close_data_std(std);
		if (result2)
			return (result2);
	}
	return (result);
}
