/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:18:21 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/05 18:25:03 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

t_token	split_command(t_queue tokens)//call je sais pas ou
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
* Goal: Expand all the element in the value of the token.
*
* Return: O if no error, or the error code corresponding.
*
* Warning: token and data must not be null.
*/
int	expand(char ***value, t_data *data, int is_redir)
{
	int	result;

	if (!*value)
		return (0);
	result = expand_env_var(value, data->env, is_redir);
	if (!*value || result)
		return (result);
	result = expand_exit_status(value, data->last_exit);
	if (!*value || result)
		return (result);
	result = expand_tilde(value, data->env, is_redir);
	if (!*value || result)
		return (result);
	result = expand_wildcard(value, is_redir);
	if (!*value || result)
		return (result);
	result = remove_quotes(value);
	return (result);
}

/*
* Goal: Find the length of the value afted being quoted.
*
* Return: The new length.
*
* Warning: value must not be null.
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
*
* Warning: value and quoted_value must not be null.
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
