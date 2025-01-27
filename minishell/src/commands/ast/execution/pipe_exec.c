/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:50:44 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/22 11:37:00 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	fork_pipe(t_data *data, t_tree *sub_tree, t_stack **stack, int is_last)
{
	int	pid;
	int	result;

	if (pipe(data->fd) == -1)
	{
		ft_putendl_error("pipe failed");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		ft_putendl_error(ERR_FORK);
		return (1);
	}
	if (pid == 0)
	{
		close(data->fd[0]);
		if (!is_last)
		{
			result = dup2(data->fd[1], STDOUT_FILENO);
			close(data->fd[1]);
			if (result < 0)
			{
				ft_printf_fd(2, "%s: %s\n", NAME, ERR_DUP2);
				exit_exec(data, result);
			}
		}
		else
			close(data->fd[1]);
		stack_clear(stack);
		result = tree_exec(data, sub_tree, 1);
		exit_exec(data, result);
	}
	close(data->fd[1]);
	if (!is_last)
	{
		result = dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[0]);
		if (result < 0)
		{
			ft_printf_fd(2, "%s: %s\n", NAME, ERR_DUP2);
			return (result);
		}
	}
	else
		close(data->fd[0]);
	result = stack_push(stack, pid);
	return (result);
}

static int	pipeline_manager(t_data *data, t_tree *tree, t_stack **stack)
{
	int	result;

	if (tree->left->token.name == TOKEN_PIPE)
		result = pipeline_manager(data, tree->left, stack);
	else
		result = fork_pipe(data, tree->left, stack, 0);
	if (result)
		return (result);
	if (tree->right->token.name == TOKEN_PIPE)
		result = pipeline_manager(data, tree->right, stack);
	else
	{
		result = fork_pipe(data, tree->right, stack, 1);
	}
	return (result);
}

static int	wait_children(t_stack *stack)
{
	int	result;
	int	pid;
	int	last_pid;
	int	status;

	result = -1;
	last_pid = stack_pop(&stack);
	pid = waitpid(-1, &status, 0);
	if (pid == last_pid)
		result = status;
	while (!stack_is_empty(stack))
	{
		stack_pop(&stack);
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
			result = status;
	}
	return (result);
}

int	pipe_exec(t_data *data, t_tree *tree)
{
	int		result;
	int		result2;
	t_stack	*stack;

	stack_init(&stack);
	result = dup_data_std(data);
	if (result)
		return (result);
	result = pipeline_manager(data, tree, &stack);
	result2 = dup2_data_std(data);
	close_data_std(data);
	if (result || result2)
	{
		stack_clear(&stack);
		if (result2)
			return (result2);
		return (result);
	}
	result = wait_children(stack);
	return (result);
}
