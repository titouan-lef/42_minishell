/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:46:52 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/08 18:19:54 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Get the first element of the queue.
*
* Return: A token.
*
* Warning: Queue mustn't be null.
*/
t_token_name	queue_first_name(t_queue *queue)
{
	return (queue->head->token.name);
}
