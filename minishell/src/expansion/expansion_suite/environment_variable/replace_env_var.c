/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/10 16:45:31 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/*
* Goal: Find the lenght the word until next quote or after replacing the env.
*
* Return: The length of the new word.
*/
static int	mesure_length(char **word, char **env, int in_double_quote)
{
	char	*env_var_value;
	int		length;

	if (in_double_quote)
	{
		length = 1;
		while (*(*word + length) && *(*word + length) != '\'')
			length++;
		if (*(*word + length))
			length++;
		(*word) += length;
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
*/
static int	new_lenght(char *word, char **env_local, int here_doc)
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
		else if (!here_doc && *word == '\'' && !in_double_quotes)
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
* Goal: Add the value of the env var in new_word.
*/
static void	update_env_var(char **word, char *new_word, int *letter, char **env)
{
	char	*env_var_value;

	(*word)++;
	env_var_value = get_quoted_value(*word, env);
	if (env_var_value)
	{
		ft_strcpy(new_word + *letter, env_var_value);
		*letter += ft_strlen(env_var_value);
	}
	while (ft_isalnum(**word) || **word == '_')
		(*word)++;
	free(env_var_value);
}

/*
* Goal: Do not replace env var in the there '<<' in a redir.
*
* Return: 1 if the here_doc is found, 0 if not.
*/
static int	do_not_replace(char *updated_word, char *word,
	int letter, int condition)
{
	if (condition && ft_strncmp(word, "<<", 2) == 0)
	{
		ft_strlcpy(updated_word + letter, word, ft_strlen(word) + 1);
		return (1);
	}
	return (0);
}

/*
* Goal: Built a new word within all the environement variables
*		in the given word are replaced with there value in env.
*
* Return: The new word.
*/
char	*replace_word_env(char *word, char **env, int here_doc, int redir)
{
	int		letter;
	char	*updated_word;
	int		in_double_quotes;

	letter = 0;
	in_double_quotes = 0;
	updated_word = ft_calloc(new_lenght(word, env, here_doc) + 1, sizeof(char));
	while (updated_word && *word)
	{
		if (do_not_replace(updated_word, word, letter, !here_doc && redir))
			break ;
		if (*word == '"')
			in_double_quotes = !in_double_quotes;
		if (*word == '$' && (*(word + 1) == '\'' || *(word + 1) == '\"')
			&& !in_double_quotes)
			word++;
		else if (*word == '$')
			update_env_var(&word, updated_word, &letter, env);
		else if (!here_doc && *word == '\'' && !in_double_quotes)
			letter = update_quote(&word, updated_word, letter);
		else
			updated_word[letter++] = *word++;
	}
	return (updated_word);
}
