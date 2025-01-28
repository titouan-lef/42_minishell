/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:18:21 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/28 16:17:30 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

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
	if (result)
		return (result);
	result = expand_exit_status(value, data->last_exit);
	if (result)
		return (result);
	result = expand_wildcard(value);
	if (result)
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
