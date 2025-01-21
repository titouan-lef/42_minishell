/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:50:44 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/21 11:46:42 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	fork_management(t_data *data, t_tree *sub_tree, t_stack **stack)
{
	int	pid;
	int	result;

	if (pipe(data->fd) == -1)
	{
		ft_putendl_error("fork failed");
		return (1);
	} 
	pid = fork();
	if (pid == -1)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		ft_putendl_error("fork failed");
		return (1);
	}
	if (pid == 0)
	{
		//if (!last)
		//{
		close(data->fd[0]);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			ft_printf_fd(2, "%s: %s\n", NAME, DUP2); //need to do something ?? for exemple don't do the command ?
		close(data->fd[1]);
		//}
		stack_clear(stack);
		result = tree_execution(data, sub_tree, 1);
		exit_exec(data, result);
	}
	// if (!last)
	// {
	close(data->fd[1]);
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		ft_printf_fd(2, "%s: %s\n", NAME, DUP2); //need to do something ?? for exemple don't do the command ?
	close(data->fd[0]);
	// }
	// else
	// {
	// close(data->fd[1]);
	// close(data->fd[0]);
	// dup2(data->std[0], STDIN_FILENO); //protections
	// dup2(data->std[1], STDOUT_FILENO);
	// dup2(data->std[2], STDERR_FILENO);
	// close(data->std[0]);
	// close(data->std[1]);
	// close(data->std[2]);
	// }
	result = stack_push(stack, pid);
	return (result);
}

static int	sub_pipe_execution(t_data *data, t_tree *tree, t_stack **stack)
{
	int	result;

	if (tree->left->token.name == TOKEN_PIPE)
		result = sub_pipe_execution(data, tree->left, stack);
	else
		result = fork_management(data, tree->left, stack);
	if (result)
		return (result);
	if (tree->right->token.name == TOKEN_PIPE)
		result = sub_pipe_execution(data, tree->right, stack);
	else
	{
		result = fork_management(data, tree->right, stack);
	}
	return (result);
}

static int	wait_children(t_stack *stack)
{
	int		result;
	int		pid;
	int		last_pid;
	int		status;

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

int	pipe_execution(t_data *data, t_tree *tree)
{
	int		result;
	t_stack	*stack;

	stack_init(&stack);
	result = sub_pipe_execution(data, tree, &stack);
	if (result)
	{
		stack_clear(&stack);
		return (result);
	}
	result = wait_children(stack);
	return (result);
}
