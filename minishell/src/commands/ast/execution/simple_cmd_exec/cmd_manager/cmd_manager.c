/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:34:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/24 20:33:37 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
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

static int	builtin_manager(char **cmd, char ***env)
{
	int	result;

	(void)env;
	result = 0;
	if (!ft_strcmp(cmd[0], "echo"))
		echo(cmd);
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

static void	execve_manager(char **cmd, char **env)
{
	char	*path;
	int		result;

	path = NULL;
	result = update_cmd_path(&path, cmd[0], env);
	if (result)
		exit(result); //free data so need the whole data struct
	execve(path, cmd, env);
	ft_printf_fd(2, "%s: %s\n", cmd[0], ERR_NO_CMD);
	free(path);
	exit (127); //free data so need the whole data struct
}

static int	fork_cmd(char **cmd, char **env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_FORK);
		return (1);
	}
	if (pid == 0)
		execve_manager(cmd, env);
	waitpid(pid, NULL, 0);
	return (0);
}

int	cmd_manager(t_token token, char ***env, int is_piped)
{
	int		result;
	char	**cmd;

	cmd = token.value;
	result = 0;
	if (is_builtin_cmd(cmd[0]))
		result = builtin_manager(cmd, env); // compress 2 functions in 1 ?
	else if (!is_piped)
		result = fork_cmd(cmd, *env);
	else
		execve_manager(cmd, *env);
	return (result);
}
