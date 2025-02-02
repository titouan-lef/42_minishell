/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/02 14:00:40 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Find the value of the 'name' env var int the env_local.
*
* Return: The value of the env var.
*
* Warning: name and env_local must not be null.
*/
static char	*get_value(char *name, char **env_local)
{
	int		name_length;

	name_length = 0;
	while (ft_isalnum(*(name + name_length)) || *(name + name_length) == '_')
		name_length++;
	if (!name_length)
		return ("$");
	while (*env_local && name_length)
	{
		if (ft_strncmp(name, *env_local, name_length) == 0
			&& *(*env_local + name_length) == '=')
			return (*env_local + name_length + 1);
		env_local++;
	}
	return (NULL);
}

/*
* Goal: Find the value of the 'name' env var int the env_local
*		and quote the quotes.
*
* Return: The quoted value of the env var.
*
* Warning: name and env_local must not be null.
*/
static char	*get_quoted_value(char *name, char **env_local)
{
	int		i;
	char	*value;
	char	*quoted_value;

	value = get_value(name, env_local);
	if (!value)
		return (NULL);
	quoted_value = ft_calloc(value_length_quoted(value) + 1, sizeof(char));
	if (!quoted_value)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (NULL);
	}
	i = 0;
	while (*value)
	{
		quote_value(value, quoted_value, &i);
		value++;
	}
	return (quoted_value);
}

/*
* Goal: Find the length of the word until next quote.
*
* Return: The length of the new word.
*
* Warning: word and env_local must not be null.
*/
static int	mesure_length(char **word, char **env, int in_double_quote)
{
	char	*env_var_value;
	int		length;

	if (in_double_quote)
	{
		length = 1;
		(*word)++;
		while (**word != '\'')
		{
			length++;
			(*word)++;
		}
		length++;
		(*word)++;
		return (length);
	}
	env_var_value = get_quoted_value(*word, env);
	if (env_var_value)
	{
		length = ft_strlen(env_var_value);
		free(env_var_value);
		return (length);
	}
	return (0);
}

/*
* Goal: Find the length of the word after replacing the env var by there value.
*
* Return: The length of the new word.
*
* Warning: word and env_local must not be null.
*/
int	new_word_lenght(char *word, char **env_local)
{
	int		length;
	int		in_double_quotes;

	length = 0;
	in_double_quotes = 0;
	while (*word)
	{
		if (*word == '\"')
			in_double_quotes = !in_double_quotes;
		if (*word == '$')
		{
			word++;
			length += mesure_length(&word, env_local, 0);
			while (ft_isalnum(*word) || *word == '_')
				word++;
		}
		else if (*word == '\'' && !in_double_quotes)
			length += mesure_length(&word, NULL, 1);
		else
		{
			length++;
			word++;
		}
	}
	return (length);
}

/*
* Goal: Add the value of the env var in the buffer "n_word".
*
* Return: None.
*
* Warning: word, new_word, letter and env_local must not be null.
*/
int	update_env_var(char **word, char *new_word, int *letter, char **env)
{
	char	*env_var_value;

	(*word)++;
	env_var_value = get_quoted_value(*word, env);
	if (env_var_value)
	{
		ft_strlcpy(new_word + *letter, env_var_value,
			ft_strlen(env_var_value) + 1);
		*letter += ft_strlen(env_var_value);
	}
	while (ft_isalnum(**word) || **word == '_')
		(*word)++;
	free(env_var_value);
	return (1);
}
