/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:39:03 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/29 16:07:38 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static t_token_name	get_redir(const char *input, int *index, char *buffer);

/*
* Goal: Put the next lettres un buffer until it is not a specal character.
*
* Return: Nothing, as buffer is pointer.
*
* Warning: input, index and buffer must not be null.
*/
static t_token_name	get_word(const char *input, int *index, char *buffer)
{
	t_token_name	token_name;
	int				start;

	start = *index;
	while (input[*index]
		&& (!ft_is_in_charset("&|()<> \t\n\v\r\f", input[*index])
			|| (input[*index] == '&' && input[*index + 1] != '&')))
	{
		if (input[*index] == '\'' || input[*index] == '\"')
		{
			if (get_quote(input, index, input[*index]))
				return (TOKEN_ERROR);
		}
		else
			(*index)++;
	}
	ft_strlcpy(buffer, input + start, *index - start + 1);
	if ((input[*index] == '<' || input[*index] == '>')
		&& ft_to_positive_int(buffer) != -1)
	{
		token_name = get_redir(input, index, buffer + *index - start);
		return (token_name);
	}
	return (TOKEN_WORD);
}

/*
* Goal: Found out if the token is an opperator, pipe or parenthesis.
*
* Return: The enum of the token type, TOKEN_NULL if none of them.
*
* Warning: input, index and buffer must not be null.
*/
static t_token_name	get_operator(const char *input, int *index, char *buffer)
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
static t_token_name	get_redir(const char *input, int *index, char *buffer)
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

/*
* Goal: Put the token found in buffer.
*
* Return: The enum of the token type.
*
* Warning: input, index and buffer must not be null.
*/
t_token_name	get_token(char *input, int *index, char *buffer)
{
	t_token_name	token_name;

	while (ft_isspace(input[*index]))
		(*index)++;
	token_name = get_operator(input, index, buffer);
	if (token_name != TOKEN_NULL)
		return (token_name);
	token_name = get_redir(input, index, buffer);
	if (token_name != TOKEN_NULL)
		return (token_name);
	token_name = get_word(input, index, buffer);
	if (token_name != TOKEN_ERROR && *buffer == '\0')
		return (TOKEN_NULL);
	return (token_name);
}
