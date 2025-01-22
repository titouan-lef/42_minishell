/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:54:18 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/22 22:32:21 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

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
	char	*buffer;

	tokens = queue_create();
	index = 0;
	while (input[index] != '\0')
	{
		buffer = (char *)ft_calloc(ft_strlen(input) + 1, sizeof(char)); //separate
		token.value = (char **)ft_calloc(2, sizeof(char *));
		if (!buffer || !token.value)
		{
			ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
			free(buffer);
			free(token.value);
			queue_clear(&tokens);
			return (tokens);
		}																// until here
		token.value[0] = buffer;
		token.name = get_token(input, &index, buffer);
		if (token.name == TOKEN_ERROR)
		{
			token_clear(token);
			queue_clear(&tokens);
			return (tokens);
		}
		if (token.name != TOKEN_NULL)
			queue_push(&tokens, token);//protect push
		else
			token_clear(token);
	}
	return (tokens);
}
