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
			result = WEXITSTATUS(status);
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
