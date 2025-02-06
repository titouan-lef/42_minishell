/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:30:20 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/03 18:18:42 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	child(t_data *data, t_tree *sub_tree, t_stack **stack)
{
	int	result;

	close(data->fd[0]);
	result = dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[1]);
	if (result < 0)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_DUP2);
		exit_exec(data, result);
	}
	stack_clear(stack);
	result = tree_exec(data, sub_tree, 1);
	exit_exec(data, result);
}

int	first_cmd(t_data *data, t_tree *sub_tree, t_stack **stack)
{
	int	pid;
	int	result;

	if (pipe(data->fd) == -1)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_FORK);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_FORK);
		return (1);
	}
	if (pid == 0)
		child(data, sub_tree, stack);
	close(data->fd[1]);
	data->last_pipe = data->fd[0];
	result = stack_push(stack, pid);
	return (result);
}
