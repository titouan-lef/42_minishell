/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:49:28 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/06 16:48:35 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "cmd_exec.h"
#include "execution.h"
#include "expansion.h"
#include "input.h"

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
static void	execve_manager(char **cmd, char **redir, t_data *data)// move to external cmd
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
static int	fork_cmd(char **cmd, char **redir, t_data *data)// move to external cmd
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
	if (modify_sigaction(&data->act, cmd_display_handler, 0))
		return (1);
	waitpid(pid, &exit_status, 0);
	if (modify_sigaction(&data->act, interactive_mode_handler, 1))
		return (1);
	data->last_exit = WEXITSTATUS(exit_status);
	exit_status = get_signal_receive();
	if (exit_status)
		return (exit_status);
	return (data->last_exit);
}

/*
* Goal: Execute the command int the given token.
*
* Return: O if no error, 1 if the fork failed.
*
* Warning: token.value and data must not be null.
*/
static int	cmd_manager(t_token token, t_data *data, int is_piped)
{
	int		result;
	char	**cmd;
	char	**redir;

	cmd = token.value;
	redir = token.redir;
	if (!cmd && !redir)
		return (0);
	result = 0;
	if (cmd && is_builtin_cmd(cmd[0]))
		result = builtin_manager(cmd, redir, data, is_piped);//manage signal
	else if (!is_piped)
		result = fork_cmd(cmd, redir, data);
	else
	{
		//close_data_std(data);
		execve_manager(cmd, redir, data);
	}
	return (result);
}

/*
* Goal: Execute the command of the given token.
*
* Return: O if no error, or the error code corresponding.
*
* Warning: token, tree and data must not be null.
*/
int	cmd_exec(t_data *data, t_token *token, int is_piped)
{
	int	result;

	result = expand(&token->value, data, 0);
	if (result)
	{
		if (is_piped)
			exit_exec(data, result);
		return (result);
	}
	result = expand(&token->redir, data, 1);
	if (result)
	{
		if (is_piped)
			exit_exec(data, result);
		return (result);
	}
	result = cmd_manager(*token, data, is_piped);
	if (is_piped)
		exit_exec(data, result);
	return (result);
}
