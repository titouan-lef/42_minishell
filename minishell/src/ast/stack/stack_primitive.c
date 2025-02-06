/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_primitive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:39:39 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/15 17:17:28 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
* Goal: Look if the given stack is empty.
*
* Return: 1 if stack is empty, 0 of not.
*/
int	stack_is_empty(t_stack *stack)
{
	return (stack == NULL);
}

/*
* Goal: Add a new pid at the end of the stack.
*
* Return: 0 if goes as expected, 1 in case of malloc problem.
*
* Warning: Stack mustn't be null.
*/
int	stack_push(t_stack **stack, pid_t pid)
{
	t_stack	*element;

	element = (t_stack *)malloc(sizeof(t_stack));
	if (!element)
	{
		ft_putendl_error("Error malloc stack push");
		return (1);
	}
	element->pid = pid;
	element->next = *stack;
	*stack = element;
	return (0);
}

/*
* Goal: Remove the first element of the stack.
*
* Return: The removed pid.
*
* Warning: Stack mustn't be null.
*/
pid_t	stack_pop(t_stack **stack)
{
	t_stack	*element;
	pid_t	pid;

	element = *stack;
	*stack = element->next;
	pid = element->pid;
	free(element);
	return (pid);
}

/*
* Goal: Remove and free all the elements of the stack.
*
* Warning: Stack mustn't be null.
*/
void	stack_clear(t_stack **stack)
{
	t_stack	*element;

	while (!stack_is_empty(*stack))
	{
		element = *stack;
		*stack = element->next;
		free(element);
	}
}

/*
* Goal: Initialize the stack.
*
* Return: The initialized stack.
*/
void	stack_init(t_stack **stack)
{
	*stack = NULL;
}
