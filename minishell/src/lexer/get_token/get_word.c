/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:03:47 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/07 13:41:43 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
* Goal: Detect the end of the quote.
*
* Warning: input, index must not be null.
*/
static int	get_quote(const char *input, int *index, char c)
{
	(*index)++;
	while (input[*index] && input[*index] != c)
		(*index)++;
	if (!input[*index])
	{
		ft_printf_fd(2, "%s: syntax error: unclosed quote `%c'\n", NAME, c);
		return (1);
	}
	(*index)++;
	return (0);
}

static t_token_name	detect_redir(const char *input, int *index,
	char *buffer, int start)
{
	t_token_name	token_name;
	int				status;

	if (ft_isdigit(*buffer))
		ft_to_number(buffer, &status, INT_MAX);
	else
		status = 1;
	if ((input[*index] == '<' || input[*index] == '>') && status == 0)
	{
		token_name = get_redir(input, index, buffer + *index - start);
		return (token_name);
	}
	return (TOKEN_WORD);
}

/*
* Goal: Put the next lettres un buffer until it is not a specal character.
*
* Return: Nothing, as buffer is pointer.
*
* Warning: input, index and buffer must not be null.
*/
t_token_name	get_word(const char *input, int *index, char *buffer)
{
	t_token_name	token_name;
	int				start;

	start = *index;
	while (input[*index])
	{
		if (input[*index] == '&' && input[*index + 1] == '&')
			break ;
		if (ft_is_in_charset("|()<> \t\n\v\r\f", input[*index]))
			break ;
		if (input[*index] == '\'' || input[*index] == '\"')
		{
			if (get_quote(input, index, input[*index]))
				return (TOKEN_ERROR);
		}
		else
			(*index)++;
	}
	ft_strlcpy(buffer, input + start, *index - start + 1);
	token_name = detect_redir(input, index, buffer, start);
	return (token_name);
}
