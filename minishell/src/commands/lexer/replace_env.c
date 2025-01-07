/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/07 18:17:02 by lguerbig         ###   ########.fr       */
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
			env_var_value = get_value(word, env_local);
			while (ft_isalnum(*word) || *word == '_')
				word++;
			if (env_var_value)
				length += ft_strlen(env_var_value);
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
static void	update_env_var(char **word, char *new_word, int *letter, char **env)
{
	char	*env_var_value;

	(*word)++;
	env_var_value = get_value(*word, env);
	if (env_var_value)
	{
		ft_strlcpy(new_word + *letter, env_var_value,
			ft_strlen(env_var_value) + 1);
		*letter += ft_strlen(env_var_value);
	}
	while (ft_isalnum(**word) || **word == '_')
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
static char	*replace_word(char *word, char **env_local)
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
		else
		{
			updated_word[letter] = *word;
			letter++;
			word++;
		}
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
int	replace_env_var(t_queue *tokens, char **env_local)
{
	int			num_word;
	t_element	*list_tokens;
	char		*updated_word;

	list_tokens = tokens->head;
	while (list_tokens)
	{
		if (list_tokens->token.name == TOKEN_CMD)
		{
			num_word = 0;
			while (list_tokens->token.value[num_word])
			{
				updated_word = replace_word(list_tokens->token.value[num_word],
						env_local);
				if (!updated_word)
					return (0);
				free(list_tokens->token.value[num_word]);
				list_tokens->token.value[num_word] = updated_word;
				num_word++;
			}
		}
		list_tokens = list_tokens->next;
	}
	return (1);
}
