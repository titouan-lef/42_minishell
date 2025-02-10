/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:54:18 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/05 18:13:34 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
* Goal: Put the token found in buffer.
*
* Return: The enum of the token type.
*/
static t_token_name	get_token(char *input, int *index, char *buffer)
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

/*
* Goal: Fill a token whith the input.
*		Set the index for next detection.
*
* Return: 0 on success, 1 if malloc error.
*/
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
	token->redir = NULL;
	token->name = get_token(input, index, buffer);
	return (0);
}

/*
* Goal: Add the token to the queue if valid token_name.
*		Clear the token if it is not.
*
* Return: 0 on success, 1 if malloc error.
*/
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
* Goal: Find all the tokens from the input command.
*		Add each token found to the queue 'tokens'.
*
* Return: 0 on success, 1 on failure.
*/
int	lexer(char *input, t_queue *tokens)
{
	int		index;
	t_token	token;

	*tokens = queue_create();
	index = 0;
	while (input[index] != '\0')
	{
		if (init_token(&token, input, &index))
		{
			queue_clear(tokens);
			return (1);
		}
		if (token.name == TOKEN_ERROR)
		{
			token_clear(token);
			queue_clear(tokens);
			return (2);
		}
		if (push_or_free(tokens, &token))
			return (1);
	}
	return (0);
}
