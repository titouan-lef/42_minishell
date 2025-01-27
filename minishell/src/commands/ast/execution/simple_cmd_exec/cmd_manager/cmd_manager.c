/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:34:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/27 18:34:08 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"

/*
* Goal: Detect a builtin function.
*
* Return: 1 if true, 0 if not.
*
* Warning: cmd_name must not be null.
*/
static int	is_builtin_cmd(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0
		|| ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "pwd") == 0
		|| ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "unset") == 0
		|| ft_strcmp(cmd_name, "env") == 0
		|| ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}

/*
* Goal: Launch the corresponding builtins command.
*
* Return: O if no error, or the error code corresponding.
*
* Warning: cmd and data must not be null.
*/
static int	builtin_manager(char **cmd, t_data *data, int is_piped)
{
	int	result;

	result = 0;
	if (!ft_strcmp(cmd[0], "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd[0], "cd"))
		result = cd(cmd, data->env);
	else if (!ft_strcmp(cmd[0], "pwd"))
		result = pwd(data->env);
	// else if (!ft_strcmp(cmd[0], "export"))
	// 	result = export(cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		result = unset(cmd, &data->env);
	// else if (!ft_strcmp(cmd[0], "env"))
	// 	result = env(cmd);
	else
		my_exit(cmd, data, is_piped);
	data->last_exit = result;
	return (result);
}

/*
* Goal: Launch any command that is not a builtin.
*
* Warning: cmd and data must not be null.
*/
static void	execve_manager(char **cmd, t_data *data)
{
	char	*path;
	int		result;

	path = NULL;
	result = update_cmd_path(&path, cmd[0], data->env);
	if (result)
	{
		clear_data(data);
		ft_clean_matrix((void **)data->env);
		exit(result);
	}
	execve(path, cmd, data->env);
	ft_printf_fd(2, "%s: %s\n", cmd[0], ERR_NO_CMD);
	free(path);
	clear_data(data);
	ft_clean_matrix((void **)data->env);
	exit (127);
}

/*
* Goal: Create a child process and execute the given command.
*
* Return: O if no error, 1 if the fork failed.
*
* Warning: cmd and data must not be null.
*/
static int	fork_cmd(char **cmd, t_data *data)
{
	int	pid;
	int	exit_satus;

	pid = fork();
	if (pid == -1)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_FORK);
		return (1);
	}
	if (pid == 0)
	{
		if (default_sigaction(&data->act))
			exit(1);// exit ?
		execve_manager(cmd, data);
	}
	waitpid(pid, &exit_satus, 0);
	data->last_exit = WEXITSTATUS(exit_satus);
	return (0);
}

/*
* Goal: Execute the command int the given token.
*
* Return: O if no error, 1 if the fork failed.
*
* Warning: token.value and data must not be null.
*/
int	cmd_manager(t_token token, t_data *data, int is_piped)
{
	int		result;
	char	**cmd;

	cmd = token.value;
	result = 0;
	if (is_builtin_cmd(cmd[0]))
		result = builtin_manager(cmd, data, is_piped); // compress 2 functions in 1 ?
	else if (!is_piped)
		result = fork_cmd(cmd, data);
	else
		execve_manager(cmd, data);
	return (result);
}
