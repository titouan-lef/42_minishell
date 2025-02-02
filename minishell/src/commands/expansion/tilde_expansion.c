/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/02 17:12:30 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "builtins.h"

/*
* Goal: Make a new word with all the environement variables
*		in the given word from there value in env_local.
*
* Return: The updated word.
*
* Warning: word and env_local must not be null.
*/
static char	*replace_word_tilde(char *word, char *home, int length)
{
	char	*updated_word;
	int		letter;

	letter = 0;
	updated_word = ft_calloc(length + ft_strlen(word) + 1, sizeof(char));
	if (!updated_word)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (NULL);
	}
	while (updated_word && *word)
	{
		if (*word == '~')
		{
			ft_strlcpy(updated_word + letter, home, length + 1);
			letter += length;
			word++;
		}
		else if (*word == '\'' || *word == '\"' )
			letter = update_quote(&word, updated_word, letter);
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
int	expand_tilde(char ***value, char **env)
{
	int		i;
	int		length;
	char	*updated_word;
	char	*home;

	i = 0;
	while ((*value)[i])
	{
		if (ft_strnstr((*value)[i], "~", ft_strlen((*value)[i])))
		{
			home = get_from_env(env, "HOME");
			if (home)
			{
				length = ft_strlen(home);
				updated_word = replace_word_tilde((*value)[i], home, length);
				free(home);
				if (!updated_word)
					return (1);
				free((*value)[i]);
				(*value)[i] = updated_word;
			}
		}
		i++;
	}
	return (0);
}
