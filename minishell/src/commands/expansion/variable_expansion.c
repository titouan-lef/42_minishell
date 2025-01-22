/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/22 01:51:01 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Copy word in updated word untill the next quote '.
*
* Warning: word, updated_word and letter must not be null.
*/
static int	update_quote(char **word, char *updated_word, int letter)
{
	updated_word[letter++] = *(*word)++;
	while (**word != '\'')
		updated_word[letter++] = *(*word)++;
	updated_word[letter++] = *(*word)++;
	return (letter);
}

/*
* Goal: Make a new word with all the environement variables
*		in the given word from there value in env_local.
*
* Return: The updated word.
*
* Warning: word and env_local must not be null.
*/
char	*replace_word_env(char *word, char **env_local, int here_doc)
{
	int		letter;
	char	*updated_word;
	int		in_double_quotes;

	letter = 0;
	updated_word = ft_calloc(new_word_lenght(word, env_local) + 1,
			sizeof(char));
	if (!updated_word)
		return (NULL);
	in_double_quotes = 0;
	while (*word)
	{
		if (!here_doc && ft_strncmp(word, "<<", 2) == 0)
			break ;
		if (*word == '"')
			in_double_quotes = !in_double_quotes;
		if (*word == '$')
			update_env_var(&word, updated_word, &letter, env_local);
		else if (!here_doc && *word == '\'' && !in_double_quotes)
			letter = update_quote(&word, updated_word, letter);
		else
			updated_word[letter++] = *word++;
	}
	return (updated_word);
}

/*
* Goal: Make a new word with all the environement variables
*		in the given word from there value in env_local.
*
* Return: The updated word.
*
* Warning: word and env_local must not be null.
*/
static char	**update_value(char **updated_value, char *updated_word)
{
	t_queue	tmp;
	t_token	splited;

	tmp = auto_tokenizer(updated_word);
	free(updated_word);
	splited = split_command(tmp);
	if (splited.value)
	{
		updated_value = tab_join_and_free(updated_value, splited.value);
		if (!updated_value)
		{
			ft_putendl_error("malloc error");
			return (NULL);
		}
	}
	return (updated_value);
}

/*
* Goal: Replace all the environement variables in all the TOKEN_CMD tokens
*		from there value in env_local.
*
* Return: 0 if errror, 1 if not.
*
* Warning: token and env_local must not be null.
*/
int	expand_env_var(t_token *token, char **env_local)
{
	int		i;
	char	*updated_word;
	char	**updated_value;

	if (token->name == TOKEN_CMD || token->name == TOKEN_REDIR)
	{
		updated_value = NULL;
		i = 0;
		while (token->value[i])
		{
			updated_word = replace_word_env(token->value[i], env_local, 0);
			if (!updated_word)
			{
				ft_putendl_error("malloc error");
				return (0);
			}
			updated_value = update_value(updated_value, updated_word);
			if (!updated_value)
				return (0);
			i++;
		}
		ft_clean_matrix((void **)token->value);
		token->value = updated_value;
	}
	return (1);
}
