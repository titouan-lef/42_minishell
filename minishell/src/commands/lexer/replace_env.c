/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/04 13:54:33 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_value(char *name, char **env_local)
{
	int		name_length;

	name_length = 0;
	while (ft_isalnum(*(name + name_length)) || *(name + name_length) == '_')
		name_length++;
	while (*env_local)
	{
		if (ft_strncmp(name, *env_local, name_length) == 0)
			return(*env_local + name_length + 2);
		env_local++;
	}
	return (NULL);
}

static int	new_word_lenght(char *word, char **env_local)
{
	int	length;
	char	*env_var_value;

	length = 0;
	while(*word)
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

static char	*updated_cmd(char *word, char **env_local)
{
	int		letter;
	char	*updated_word;
	char	*env_var_value;

	letter = 0;
	updated_word = ft_calloc(sizeof(char), new_word_lenght(word, env_local) + 1);
	while (word[letter])
	{
		env_var_value = NULL;
		if (word[letter] == '$')
		{	
			letter++;
			env_var_value = get_value(word + letter, env_local);
			while (ft_isalnum(*(word + letter)) || *(word + letter) == '_')
				letter++;
			if (env_var_value)
				ft_strlcpy(updated_word, env_var_value, ft_strlen(env_var_value));
		}
		else
		{
			updated_word[letter] = word[letter];
			letter++;
		}
	}
	return (updated_word);
}

void	replace_env_var(t_queue *tokens, char **env_local)
{
	int			num_word;
	t_element	*list_tokens;
	char		*updated_word;

	list_tokens = tokens->head;
	while(list_tokens)
	{
		if (list_tokens->token.name == TOKEN_CMD)
		{
			num_word = 0;
			while (list_tokens->token.value[num_word])
			{
				updated_word = updated_cmd(list_tokens->token.value[num_word], env_local);
				free(list_tokens->token.value[num_word]);
				list_tokens->token.value[num_word] = updated_word;
				num_word++;
			}
		}
		list_tokens = list_tokens->next;
	}
}
