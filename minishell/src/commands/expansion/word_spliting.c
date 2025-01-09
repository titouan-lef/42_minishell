/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_spliting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/09 13:50:19 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Find the length of the new tab after removing the quotes.
*
* Return: The length of the new tab.
*
* Warning: value must not be null.
*/
static int	new_nb_word(char **value)
{
	int		i;
	int		nb_words;
	char	**tmp;

	nb_words = 0;
	while (*value)
	{
		i = 0;
		nb_words++;
		while (*value[i])
		{
			if (ft_isspace(*value[i]))
				nb_words++;
			i++;
		}
	}
	return (nb_words);
}

/*
* Goal: Make a new word with all the environement variables
*		in the given word from there value in env_local.
*
* Return: The updated word.
*
* Warning: word and env_local must not be null.
*/
static char	*replace_word(char *word)
{
	int		letter;
	char	*updated_word;

	letter = 0;
	updated_word = ft_calloc(sizeof(char),new_word_lenght(word) + 1);
	if (!updated_word)
		return (NULL);
	while (*word)
	{
		if (*word == '\'')
		{
			word++;
			while (*word != '\'')
				updated_word[letter++] = *word++;
			word++;
		}
		else if (*word == '\"')
			word++;
		else
			updated_word[letter++] = *word++;
	}
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
int	split_words(t_token *token)
{
	int			num_word;
	char		**updated_value;
	char		**tmp;

	if (token->name == TOKEN_CMD || token->name == TOKEN_REDIR)
	{
		updated_value = ft_calloc(new_nb_word(token->value), sizeof(char *));
		num_word = 0;
		while (token->value[num_word])
		{
			tmp = ft_split_charset(token->value[num_word], " \t\n\v\f\r");
			if (!tmp)
			{
				ft_putendl_error("Malloc Error");
				return (0);
			}
			while(*tmp)
				updated_value[num_word++] = *tmp++;
			free(tmp);
			num_word++;
		}
	}
	ft_clean_matrix((void **)token->value);
	token->value= updated_value;
	return (1);
}
