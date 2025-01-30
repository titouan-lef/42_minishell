/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:34:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/30 12:06:28 by tle-floc         ###   ########.fr       */
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
* Goal: Launch any command that is not a builtin.
*
* Warning: cmd and data must not be null.
*/
static void	execve_manager(char **cmd, char **redir, t_data *data)
{
	char	*path;
	int		result;

	if (default_sigaction(&data->act))
		exit_exec(data, 1);
	result = redir_manager(redir, data->lst);
	if (result || !cmd)
		exit_exec(data, result);
	path = NULL;
	result = update_cmd_path(&path, cmd[0], data->env);
	if (result)
		exit_exec(data, result);
	execve(path, cmd, data->env);
	ft_printf_fd(2, "%s: %s: %s\n", NAME, cmd[0], ERR_NO_CMD);
	free(path);
	exit_exec(data, 127);
}

/*
* Goal: Create a child process and execute the given command.
*
* Return: O if no error, 1 if the fork failed.
*
* Warning: cmd and data must not be null.
*/
static int	fork_cmd(char **cmd, char **redir, t_data *data)
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
		execve_manager(cmd, redir, data);
	if (modify_sigaction(&data->act, cmd_display_handler))
		return (1);
	waitpid(pid, &exit_satus, 0);
	if (modify_sigaction(&data->act, interactive_mode_handler))
		return (1);
	data->last_exit = WEXITSTATUS(exit_satus);// autorise ?
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
	char	**redir;

	cmd = token.value;
	redir = token.redir;
	result = 0;
	if (cmd && is_builtin_cmd(cmd[0]))
		result = builtin_manager(cmd, redir, data, is_piped);//manage signal
	else if (!is_piped)
		result = fork_cmd(cmd, redir, data);
	else
	{
		close_data_std(data);
		execve_manager(cmd, redir, data);
	}
	return (result);
}
