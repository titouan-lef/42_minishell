/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:39:03 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/12 18:58:14 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static t_token_name	get_redir(const char *input, int *index, char *buffer);

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

int	is_int(char *str) // TODO: remake without atol and put into libft
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	while (*str == '0')
		str++;
	if (ft_strlen(str) > 10)
		return (0);
	if (atol(str) > INT_MAX)
		return (0);
	return (1);
}

/*
* Goal: Put the next lettres un buffer until it is not a specal character.
*
* Return: Nothing, as buffer is pointer.
*
* Warning: input, index and buffer must not be null.
*/
static t_token_name	get_word(const char *input, int *index, char *buffer)
{
	int	start ;

	start = *index;
	while (input[*index] && !ft_is_in_charset("&|()<> ", input[*index]))
	{
		if (input[*index] == '\'')
		{
			(*index)++;
			while (input[*index] && input[*index] != '\'')
				(*index)++;
			(*index)++;
		}
		else if (input[*index] == '\"')
		{
			(*index)++;
			while (input[*index] && input[*index] != '\"')
				(*index)++;
			(*index)++;
		}
		else
			(*index)++;
	}
	ft_strlcpy(buffer, input + start, *index - start + 1);
	if ((input[*index] == '<' || input[*index] == '>') && is_int(buffer))
	{
		get_redir(input, index, buffer + *index - start);
		return (TOKEN_REDIR);
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
			return (TOKEN_OPE);
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
		if (cmp_and_inc(input, index, '&', buffer))
			return (TOKEN_OPE);
	return (TOKEN_NULL);
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
	char	current;

	current = input[*index];
	if (current == '<' || current == '>')
	{
		(*index)++;
		if (input[*index] == current)
		{
			(*index)++;
			buffer[1] = current;
			while (ft_isspace(input[*index]))
				(*index)++;
			get_word(input, index, buffer + 2);
		}
		else
		{
			while (ft_isspace(input[*index]))
				(*index)++;
			get_word(input, index, buffer + 1);
		}
		buffer[0] = current;
		return (TOKEN_REDIR);
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
	if (*buffer == '\0')
		return (TOKEN_NULL);
	return (token_name);
}
