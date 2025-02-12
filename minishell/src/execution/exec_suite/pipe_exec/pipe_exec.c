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

/*
* Goal: Make the redirection and execute command regarding of his position
*		in the pipeline.
*		0b10 check if it is the first command of the pipeline.
*		0b01 check if it is the last command of the pipeline.
*
* Return: The result of redirections.
*/
static int	pipeline_manager(t_data *data, t_tree *tree,
				t_stack **stack, int pos)
{
	int	result;

	if (tree->left->token.name == TOKEN_PIPE)
		result = pipeline_manager(data, tree->left, stack, pos & 0b10);
	else
	{
		if (pos & 0b10)
			result = first_cmd(data, tree->left, stack);
		else
			result = midle_cmd(data, tree->left, stack);
	}
	if (result)
		return (result);
	if (tree->right->token.name == TOKEN_PIPE)
		result = pipeline_manager(data, tree->right, stack, pos & 0b01);
	else
	{
		if (pos & 0b01)
			result = last_cmd(data, tree->right, stack);
		else
			result = midle_cmd(data, tree->right, stack);
	}
	return (result);
}

/*
* Goal: Waits for all the child processes.
*
* Return: Last command's code or 1 if error.
*/
static int	wait_children(t_stack **stack, t_data *data)
{
	int	result;
	int	pid;
	int	last_pid;
	int	status;

	result = -1;
	last_pid = stack_pop(stack);
	if (modify_sigaction(&data->act, cmd_display_handler, 0))
		return (1);
	pid = waitpid(-1, &status, 0);
	if (pid == last_pid)
		result = WEXITSTATUS(status);
	while (!stack_is_empty(*stack))
	{
		stack_pop(stack);
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
			result = WEXITSTATUS(status);
	}
	if (modify_sigaction(&data->act, interactive_mode_handler, 1))
		return (1);
	return (result);
}

/*
* Goal: Make the redirection and execute all commands. PID are stacked
*		in 'stack' to update exit status with the last command's exit.
*
* Return: Last command's code or 1 if error.
*/
int	pipe_exec(t_data *data, t_tree *tree)
{
	int		result;
	t_stack	*stack;

	stack_init(&stack);
	result = pipeline_manager(data, tree, &stack, 0b11);
	if (result)
	{
		stack_clear(&stack);
		return (result);
	}
	result = wait_children(&stack, data);
	stack_clear(&stack);
	return (result);
}
