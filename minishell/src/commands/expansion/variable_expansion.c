/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/18 13:39:00 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Find the length of the word after replacing the env var by there value.
*
* Return: The length of the new word.
*
* Warning: word and env_local must not be null.
*/
static int	new_word_lenght(char *word, char **env_local)
{
	int		length;
	char	*env_var_value;

	length = 0;
	while (*word)
	{
		if (*word == '$')
		{
			word++;
			env_var_value = get_quoted_value(word, env_local);
			while (ft_isalnum(*word) || *word == '_')
				word++;
			if (env_var_value)
				length += ft_strlen(env_var_value);
			free(env_var_value);
		}
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
static int	update_env_var(char **word, char *new_word, int *letter, char **env)
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

/*
* Goal: Make a new word with all the environement variables
*		in the given word from there value in env_local.
*
* Return: The updated word.
*
* Warning: word and env_local must not be null.
*/
static char	*replace_word_env(char *word, char **env_local)
{
	int		letter;
	char	*updated_word;

	letter = 0;
	updated_word = ft_calloc(sizeof(char),
			new_word_lenght(word, env_local) + 1);
	if (!updated_word)
		return (NULL);
	while (*word)
	{
		if (*word == '$')
			update_env_var(&word, updated_word, &letter, env_local);
		else if (*word == '\'')
		{
			updated_word[letter++] = *word++;
			while (*word != '\'')
				updated_word[letter++] = *word++;
			updated_word[letter++] = *word++;
		}
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
	int		num_word;
	char	*updated_word;
	char	**updated_value;

	if (token->name == TOKEN_CMD || token->name == TOKEN_REDIR)
	{
		updated_value = NULL;
		num_word = 0;
		while (token->value[num_word])
		{
			updated_word = replace_word_env(token->value[num_word], env_local);
			if (!updated_word)
			{
				ft_putendl_error("malloc error");
				return (0);
			}
			updated_value = update_value(updated_value, updated_word);
			if (!updated_value)
				return (0);
			num_word++;
		}
		ft_clean_matrix((void **)token->value);
		token->value = updated_value;
	}
	return (1);
}
