/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/26 17:00:29 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Increment lenght until the quote is open.
*
* Warning: word and length must not be null.
*/
static void	skip_quotes_in_counting(char **word, int *length, char c)
{
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
*
* Warning: word must not be null.
*/
static int	shorter_word_lenght(char *word)
{
	int		length;

	length = 0;
	while (*word)
	{
		if (*word == '\'')
			skip_quotes_in_counting(&word, &length, '\'');
		else if (*word == '\"')
			skip_quotes_in_counting(&word, &length, '\"');
		else
		{
			length++;
			word++;
		}
	}
	return (length);
}

/*
* Goal: Update word until the quote is open.
*
* Warning: updated_word, word and length must not be null.
*/
static void	skip_quotes_in_replacing(char *updated_word,
		char **word, int *letter, char c)
{
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
* Return: The updated word.
*
* Warning: word and env_local must not be null.
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
		if (*word == '\'')
			skip_quotes_in_replacing(updated_word, &word, &letter, '\'');
		else if (*word == '\"')
			skip_quotes_in_replacing(updated_word, &word, &letter, '\"');
		else
			updated_word[letter++] = *word++;
	}
	return (updated_word);
}

/*
* Goal: Replace all the environement variables in all the TOKEN_CMD tokens
*		from there value in env_local.
*
* Return: 1 if errror, 0 if not.
*
* Warning: token and env_local must not be null.
*/
int	remove_quotes(t_token *token)
{
	int			num_word;
	char		*updated_word;

	if (token->name == TOKEN_CMD || token->name == TOKEN_REDIR)
	{
		num_word = 0;
		while (token->value[num_word])
		{
			updated_word = replace_word_quotes(token->value[num_word]);
			if (!updated_word)
				return (1);
			free(token->value[num_word]);
			token->value[num_word] = updated_word;
			num_word++;
		}
	}
	return (0);
}
