/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/07 15:51:56 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static int	count_replacement(char *word)
{
	int	nb_replace;
	int	in_double_quotes;

	nb_replace = 0;
	in_double_quotes = 0;
	while (*word)
	{
		if (*word == '\"')
			in_double_quotes = !in_double_quotes;
		if (*(word + 1) && *word == '$' && *(word + 1) == '?')
		{
			nb_replace++;
			word += 2;
		}
		else
			word++;
		if (*(word - 1) == '\'' && !in_double_quotes)
		{
			while (*word && *word != '\'')
				word++;
			if (*word)
				word++;
		}
	}
	return (nb_replace);
}

static void	find_and_replace(char *updated_word, char *word,
		char *exit_status, int length)
{
	int	letter;
	int	in_double_quotes;

	letter = 0;
	in_double_quotes = 0;
	length = ft_strlen(exit_status);
	while (*word)
	{
		if (*word == '\"')
			in_double_quotes = !in_double_quotes;
		if (*(word + 1) && *word == '$' && *(word + 1) == '?')
		{
			ft_strlcpy(updated_word + letter, exit_status, length + 1);
			letter += length;
			word += 2;
		}
		else if (*word == '\'' && !in_double_quotes)
			letter = update_quote(&word, updated_word, letter);
		else
			updated_word[letter++] = *word++;
	}
}

/*
* Goal: Make a new word with all the environement variables
*		in the given word from there value in env_local.
*
* Return: The updated word.
*
* Warning: word and env_local must not be null.
*/
char	*replace_word_exit(char *word, int last_exit)
{
	char	*updated_word;
	char	*exit_status;
	int		length;
	int		nb_replace;

	exit_status = ft_itoa(last_exit);
	if (!exit_status)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (NULL);
	}
	length = ft_strlen(exit_status);
	nb_replace = count_replacement(word);
	updated_word = ft_calloc(length * nb_replace + ft_strlen(word)
			- 2 * nb_replace + 1, sizeof(char));
	if (!updated_word)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (NULL);
	}
	find_and_replace(updated_word, word, exit_status, length);
	free(exit_status);
	return (updated_word);
}

/*
* Goal: Replace all the environement variables in all the TOKEN_CMD tokens
*		from there value in env_local.
*
* Return: 0 if errror, 1 if not.
*
* Warning: token and env_local must not be null.
*/
int	expand_exit_status(char ***value, int last_exit)
{
	int		i;
	char	*updated_word;

	i = 0;
	while ((*value)[i])
	{
		if (ft_strnstr((*value)[i], "$?", ft_strlen((*value)[i])))
		{
			updated_word = replace_word_exit((*value)[i], last_exit);
			if (!updated_word)
				return (1);
			free((*value)[i]);
			(*value)[i] = updated_word;
		}
		i++;
	}
	return (0);
}
