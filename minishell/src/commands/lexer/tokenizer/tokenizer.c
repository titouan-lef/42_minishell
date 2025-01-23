/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:54:18 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/23 19:59:36 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static int	init_token(t_token *token, char *input, int *index)
{
	char	*buffer;

	buffer = (char *)ft_calloc(ft_strlen(input) + 1, sizeof(char));
	token->value = (char **)ft_calloc(2, sizeof(char *));
	if (!buffer || !token->value)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		free(buffer);
		free(token->value);
		return (1);
	}
	token->value[0] = buffer;
	token->name = get_token(input, index, buffer);
	return (0);
}

static int	push_or_free(t_queue *tokens, t_token *token)
{
	if (token->name == TOKEN_NULL)
		token_clear(*token);
	else if (queue_push(tokens, *token))
	{
		token_clear(*token);
		queue_clear(tokens);
		return (1);
	}
	return (0);
}

/*
* Goal: Found all the tokens in the input command.
*
* Return: A queue of tokens.
*
* Warning: input must not be null.
*/
t_queue	tokenizer(char *input)
{
	int		index;
	t_token	token;
	t_queue	tokens;

	tokens = queue_create();
	index = 0;
	while (input[index] != '\0')
	{
		if (init_token(&token, input, &index))
		{
			queue_clear(&tokens);
			return (tokens);
		}
		if (token.name == TOKEN_ERROR)
		{
			token_clear(token);
			queue_clear(&tokens);
			return (tokens);
		}
		if (push_or_free(&tokens, &token))
			return (tokens);
	}
	return (tokens);
}
