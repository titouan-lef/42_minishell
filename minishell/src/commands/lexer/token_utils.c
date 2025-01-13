/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:39:03 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/13 19:35:47 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Compare the current input[*index] with the given char c.
*		Put the operator in buffer.
*		Increment *index i they are equal.
*
* Return: 1 if equal, 0 if not.
*
* Warning: input, index and buffer must not be null.
*/
int	cmp_and_inc(const char *input, int *index, char c, char *buffer)
{
	if (input[*index] == c)
	{
		if (*index > 0 && input[*index - 1] == c)
			buffer[1] = c;
		else
			buffer[0] = c;
		(*index)++;
		return (1);
	}
	return (0);
}
