/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:34:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/20 16:24:31 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "builtins.h"

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

static int	execute_builtin(char **cmd, char **env)
{
	int	result;

	(void)env;
	result = 0;
	if (!ft_strcmp(cmd[0], "echo"))
		echo(++cmd);
	// else if (!ft_strcmp(cmd[0], "cd"))
	// 	result = cd(cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		result = pwd();
	// else if (!ft_strcmp(cmd[0], "export"))
	// 	result = export(cmd);
	// else if (!ft_strcmp(cmd[0], "unset"))
	// 	result = unset(cmd);
	// else if (!ft_strcmp(cmd[0], "env"))
	// 	result = enc(cmd);
	else
		return (1);
	return (result);
}

static int	execute(char **cmd, char **env)
{
	char	*path;
	int		result;

	path = NULL;
	result = get_path(&path, cmd[0], env);
	if (result)
		return (result);
	execve(path, cmd, env);
	ft_printf_fd(2, "%s: %s: %s", NAME, path, NO_CMD);
	free(path);
	return (127);
}

static int	fork_and_execute(char **cmd, char **env)
{
	int	pid;
	int	result;

	pid = fork();
	if (pid == -1)
	{
		ft_printf_fd(2, "%s: %s", NAME, FORK);
		return (1);
	}
	if (pid == 0)
	{
		result = execute(cmd, env);
		if (result)
			return (result);
	}
	return (0);
}

int	execute_cmd(t_token token, char **env, int is_piped)
{
	int		result;
	char	**cmd;

	cmd = token.value;
	result = 0;
	if (is_builtin_cmd(cmd[0]))
		result = execute_builtin(cmd, env); // compress 2 functions in 1 ?
	else if (!is_piped)
		result = fork_and_execute(cmd, env);
	else
		result = execute(cmd, env);
	return (result);
}
