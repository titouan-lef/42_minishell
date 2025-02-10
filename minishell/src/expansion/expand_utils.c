/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:18:21 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/10 16:46:44 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/*
* Goal: Join all the tokens of the given queue in a unic token command.
*		All the values are joined together.
*
* Return: The token created, it is token.value is null in case or error.
*/
t_token	join_command(t_queue tokens)
{
	t_token	token;
	t_token	new_token;

	new_token = token_create(TOKEN_CMD, NULL, NULL);
	while (!queue_is_empty(&tokens))
	{
		token = queue_pop(&tokens);
		new_token.value = tab_join_and_free(new_token.value, token.value);
		if (new_token.value == NULL)
		{
			ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
			token_clear(token);
			token_clear(new_token);
			queue_clear(&tokens);
			return (new_token);
		}
	}
	queue_clear(&tokens);
	return (new_token);
}

/*
* Goal: Find the length of the value afted being quoted.
*
* Return: The new length.
*/
int	value_length_quoted(char *value)
{
	int	length;

	length = 0;
	while (*value)
	{
		length++;
		if (*value == '\"' || *value == '\'')
			length += 2;
		value++;
	}
	return (length);
}

/*
* Goal: Copy the char value[i] and quoting quotes in quoted_value .
*/
void	quote_value(char *value, char *quoted_value, int *i)
{
	if (*value == '\"')
	{
		quoted_value[(*i)++] = '\'';
		quoted_value[(*i)++] = *value;
		quoted_value[(*i)++] = '\'';
	}
	else if (*value == '\'')
	{
		quoted_value[(*i)++] = '\"';
		quoted_value[(*i)++] = *value;
		quoted_value[(*i)++] = '\"';
	}
	else
		quoted_value[(*i)++] = *value;
}

/*
* Goal: Copy word in updated word untill the next quote.
*
* Return: The lenght of the quoted sequence
*/
int	update_quote(char **word, char *updated_word, int letter)
{
	char	c;

	c = **word;
	updated_word[letter++] = *(*word)++;
	while (**word && **word != c)
		updated_word[letter++] = *(*word)++;
	if (**word)
		updated_word[letter++] = *(*word)++;
	return (letter);
}
