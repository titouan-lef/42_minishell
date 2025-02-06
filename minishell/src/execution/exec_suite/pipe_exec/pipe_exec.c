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

#include <sys/wait.h>
#include "execution.h"

static int	pipeline_manager(t_data *data, t_tree *tree, t_stack **stack, int is_first, int is_last)
{
	int	result;

	if (tree->left->token.name == TOKEN_PIPE)
		result = pipeline_manager(data, tree->left, stack, is_first, 0);
	else
	{
		if (is_first)
			result = first_cmd(data, tree->left, stack);
		else
			result = midle_cmd(data, tree->left, stack);
	}
	if (result)
		return (result);
	if (tree->right->token.name == TOKEN_PIPE)
		result = pipeline_manager(data, tree->right, stack, 0, is_last);
	else
	{
		if (is_last)
			result = last_cmd(data, tree->right, stack);
		else
			result = midle_cmd(data, tree->right, stack);
	}
	return (result);
}

static int	wait_children(t_stack *stack, t_data *data)
{
	int	result;
	int	pid;
	int	last_pid;
	int	status;

	result = -1;
	last_pid = stack_pop(&stack);
	if (modify_sigaction(&data->act, cmd_display_handler, 0))
		return (1);
	pid = waitpid(-1, &status, 0);
	if (pid == last_pid)
		result = WEXITSTATUS(status);
	while (!stack_is_empty(stack))
	{
		stack_pop(&stack);
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
			result = WEXITSTATUS(status);
	}
	if (modify_sigaction(&data->act, interactive_mode_handler, 1))
		return (1);
	return (result);
}

int	pipe_exec(t_data *data, t_tree *tree)
{
	int		result;
	t_stack	*stack;

	stack_init(&stack);
	result = pipeline_manager(data, tree, &stack, 1, 1);
	if (result)
	{
		stack_clear(&stack);
		return (result);
	}
	result = wait_children(stack, data);
	return (result);
}
