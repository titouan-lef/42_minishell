/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:49:28 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/07 14:31:56 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "expansion.h"

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
		result = builtin_manager(cmd, redir, data, is_piped);
	else
		result = external_cmd_manager(cmd, redir, data, is_piped);
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
