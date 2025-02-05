/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:04:03 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/05 18:09:04 by lguerbig         ###   ########.fr       */
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
static int	cmp_and_inc(const char *input, int *index, char c, char *buffer)
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


/*
* Goal: Found out if the token is an opperator, pipe or parenthesis.
*
* Return: The enum of the token type, TOKEN_NULL if none of them.
*
* Warning: input, index and buffer must not be null.
*/
t_token_name	get_operator(const char *input, int *index, char *buffer)
{
	if (cmp_and_inc(input, index, '|', buffer))
	{
		if (cmp_and_inc(input, index, '|', buffer))
			return (TOKEN_LOGIC_OPE);
		return (TOKEN_PIPE);
	}
	if (input[*index] == '(' )
	{
		buffer[0] = input[*index];
		(*index)++;
		return (TOKEN_PAR_OPEN);
	}
	if (input[*index] == ')')
	{
		buffer[0] = input[*index];
		(*index)++;
		return (TOKEN_PAR_CLOSE);
	}
	if (cmp_and_inc(input, index, '&', buffer))
	{
		if (cmp_and_inc(input, index, '&', buffer))
			return (TOKEN_LOGIC_OPE);
		(*index)--;
	}
	return (TOKEN_NULL);
}