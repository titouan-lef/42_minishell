/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:54:18 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/15 16:24:14 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Fill token name and token value.
*
* Return: None.
*
* Warning: input, index and buffer must not be null.
*/
static int	fill_token(t_token *token, char *input, int *index, char *buffer)
{
	token->name = get_token(input, index, buffer);
	if (token->name == TOKEN_NULL)
	{
		free(buffer);
		free(token->value);
		return (0);
	}
	token->value[0] = buffer;
	return (1);
}

/*
* Goal: Found all the tokens in the input command.
*
* Return: A queue of tokens.
*
* Warning: input must not be null.
*/
t_queue	auto_tokenizer(char *input)
{
	int		index;
	t_token	token;
	t_queue	tokens;
	char	*buffer;

	tokens = queue_create();
	index = 0;
	while (input[index] != '\0')
	{
		buffer = (char *)ft_calloc(ft_strlen(input) + 1, sizeof(char));
		token.value = (char **)ft_calloc(2, sizeof(char *));
		if (!buffer || !token.value)
		{
			ft_printf_fd(2, "malloc error");
			free(buffer);
			free(token.value);
			queue_clear(&tokens);
			return (tokens);
		}
		if (fill_token(&token, input, &index, buffer))
			queue_push(&tokens, token);
	}
	return (tokens);
}
