/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:50:44 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/17 19:05:24 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	fork_management(t_data *data, t_tree *sub_tree, t_stack **stack)
{
	int	pid;
	int	result;

	pid = fork();
	if (pid == -1)
	{
		ft_putendl_error("fork failed");
		return (1);
	}
	if (pid == 0)
	{
		stack_clear(stack);
		result = tree_execution(data, sub_tree, 1);
		exit_exec(data, result);
	}
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
		result = fork_management(data, tree->right, stack);
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
