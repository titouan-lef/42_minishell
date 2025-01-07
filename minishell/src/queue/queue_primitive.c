/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_primitive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:39:27 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/07 09:29:44 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Look if the given queue is empty.
*
* Return: 1 if queue is empty, 0 of not.
*
* Warning: Queue mustn't be null.
*/
static int	queue_is_empty(t_queue *queue)
{
	return (queue->head == NULL);
}

/*
* Goal: Add a new token at the end of the queue.
*
* Return: 1 if goes as expected, 0 in case of malloc problem.
*
* Warning: Queue mustn't be null.
*/
int	queue_push(t_queue *queue, t_token token)
{
	t_element	*element;

	element = (t_element *)malloc(sizeof(t_element));
	if (!element)
	{
		queue_clear(queue);
		ft_putendl_error("Error malloc queue push");
		return (0);
	}
	element->token = token;
	element->next = NULL;
	if (queue_is_empty(queue))
		queue->head = element;
	else
		queue->tail->next = element;
	queue->tail = element;
	return (1);
}

/*
* Goal: Remove the first element of the queue.
*
* Return: The removed token.
*
* Warning: Queue mustn't be null.
*/
t_token	queue_pop(t_queue *queue)
{
	t_element	*element;
	t_token		token;

	element = queue->head;
	queue->head = element->next;
	token = element->token;
	free(element);
	if (queue->head == NULL)
		queue->tail = NULL;
	return (token);
}

/*
* Goal: Remove and free all the elements of the queue.
*
* Return: None.
*
* Warning: Queue mustn't be null.
*/
void	queue_clear(t_queue *queue)
{
	t_element	*element;

	while (!queue_is_empty(queue))
	{
		element = queue->head;
		queue->head = element->next;
		token_clear(element->token);
		free(element);
		element = NULL;
	}
	queue->tail = NULL;
}

/*
* Goal: Create the queue.
*
* Return: The created queue.
*
* Warning: None.
*/
t_queue	queue_create(void)
{
	t_queue	queue;

	queue.head = NULL;
	queue.tail = NULL;
	return (queue);
}
