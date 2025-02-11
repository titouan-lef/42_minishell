/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/11 15:33:12 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/*
* Goal: Increment lenght and *word until next quote.
*/
static void	skip_quotes_in_counting(char **word, int *length)
{
	char	c;

	c = **word;
	(*word)++;
	while (**word && **word != c)
	{
		(*length)++;
		(*word)++;
	}
	if (**word)
		(*word)++;
}

/*
* Goal: Find the length of the word after removing the quotes.
*
* Return: The length of the new word.
*/
static int	shorter_word_lenght(char *word)
{
	int		length;

	length = 0;
	while (*word)
	{
		if (*word == '\'' || *word == '\"')
			skip_quotes_in_counting(&word, &length);
		else
		{
			length++;
			word++;
		}
	}
	return (length);
}

/*
* Goal: Update word until next quote.
*/
static void	skip_quotes_in_replacing(char *updated_word,
		char **word, int *letter)
{
	char	c;

	c = **word;
	(*word)++;
	while (**word && **word != c)
		updated_word[(*letter)++] = *(*word)++;
	if (**word)
		(*word)++;
}

/*
* Goal: Make a new word with all the environement variables
*		in the given word from there value in env_local.
*
* Return: The updated word, NULL if error.
*/
char	*replace_word_quotes(char *word)
{
	int		letter;
	char	*updated_word;

	letter = 0;
	updated_word = ft_calloc(shorter_word_lenght(word) + 1, sizeof(char));
	if (!updated_word)
	{
		ft_printf_fd(2, "%s: %s", NAME, ERR_MALLOC);
		return (NULL);
	}
	while (*word)
	{
		if (*word == '\'' || *word == '\"')
			skip_quotes_in_replacing(updated_word, &word, &letter);
		else
			updated_word[letter++] = *word++;
	}
	return (updated_word);
}

/*
* Goal: Replace all the environement variables in all the TOKEN_CMD tokens
*		from there value in env_local.
*
* Return: 0 on success, 1 on failure.
*/
int	remove_quotes(char ***value)
{
	int			num_word;
	char		*updated_word;

	num_word = 0;
	while ((*value)[num_word])
	{
		updated_word = replace_word_quotes((*value)[num_word]);
		if (!updated_word)
			return (1);
		free((*value)[num_word]);
		(*value)[num_word] = updated_word;
		num_word++;
	}
	return (0);
}
