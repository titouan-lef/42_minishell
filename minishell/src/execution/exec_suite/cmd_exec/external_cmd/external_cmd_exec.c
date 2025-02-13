/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:49:28 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/13 12:15:42 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "expansion.h"

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
	result = redir_manager(redir);
	if (result || !cmd)
		exit_exec(data, result);
	path = NULL;
	result = update_cmd_path(&path, cmd[0], data->env);
	if (result)
		exit_exec(data, result);
	rl_clear_history();
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
	int	exit_status;

	pid = fork();
	if (pid == -1)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_FORK);
		return (1);
	}
	if (pid == 0)
		execve_manager(cmd, redir, data);
	waitpid(pid, &exit_status, 0);
	exit_status = get_child_exit_status(exit_status);
	return (exit_status);
}

int	external_cmd_manager(char **cmd, char **redir, t_data *data, int is_piped)
{
	int	result;

	if (is_piped)
		execve_manager(cmd, redir, data);
	if (modify_sigaction(&data->act, cmd_display_handler, 0))
		return (1);
	result = fork_cmd(cmd, redir, data);
	if (modify_sigaction(&data->act, interactive_mode_handler, 1))
		return (1);
	return (result);
}
