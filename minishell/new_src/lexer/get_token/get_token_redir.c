/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:03:34 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/05 18:09:37 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static t_token_name	get_filename(const char *input, int *index,
		char *buffer, int offset_buffer)
{
	t_token_name	token_name;

	while (ft_isspace(input[*index]))
		(*index)++;
	token_name = get_word(input, index, buffer + offset_buffer);
	return (token_name);
}

/*
* Goal: Found out if the token is an redirection.
*
* Return: TOKEN_REDIR if the current token is a redir, TOKEN_NULL if not.
*
* Warning: input, index and buffer must not be null.
*/
t_token_name	get_redir(const char *input, int *index, char *buffer)
{
	char			current;
	t_token_name	token_name;

	current = input[*index];
	if (current == '<' || current == '>')
	{
		(*index)++;
		if (input[*index] == current)
		{
			(*index)++;
			buffer[1] = current;
			token_name = get_filename(input, index, buffer, 2);
		}
		else
			token_name = get_filename(input, index, buffer, 1);
		if (token_name == TOKEN_WORD)
			token_name = TOKEN_REDIR;
		buffer[0] = current;
		return (token_name);
	}
	return (TOKEN_NULL);
}
