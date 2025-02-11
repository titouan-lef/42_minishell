/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:30:20 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/11 19:09:14 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	child(t_data *data, t_tree *sub_tree, t_stack **stack)
{
	int	result;

	stack_clear(stack);
	result = dup2(data->last_pipe, STDIN_FILENO);
	close(data->last_pipe);
	if (result < 0)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_DUP2);
		exit_exec(data, 1);
	}
	result = tree_exec(data, sub_tree, 1);
	exit_exec(data, result);
}

/*
* Goal: Redirected the input for the command.
*
* Return: 0 on success, 1 on failure.
*/
int	last_cmd(t_data *data, t_tree *sub_tree, t_stack **stack)
{
	int	pid;
	int	result;

	pid = fork();
	if (pid == -1)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_FORK);
		close(data->last_pipe);
		return (1);
	}
	if (pid == 0)
		child(data, sub_tree, stack);
	close(data->last_pipe);
	result = stack_push(stack, pid);
	return (result);
}
