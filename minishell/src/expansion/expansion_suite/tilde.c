/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/10 16:41:09 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/*
* Goal: Fill the new word by copying the value of HOME instead of ~.
*
* Return: The updated word.
*/
static void	find_and_replace(char *updated_word, char *word,
	char *home, int is_redir)
{
	int		letter;
	int		done;
	int		length;

	length = ft_strlen(home);
	done = 0;
	letter = 0;
	while (*word)
	{
		if (!done && *word == '~' && (!*(word + 1) || *(word + 1) == '/'))
		{
			letter += ft_strlcpy(updated_word + letter, home, length + 1);
			word++;
		}
		else if (*word == '\'' || *word == '\"')
			letter = update_quote(&word, updated_word, letter);
		else
			updated_word[letter++] = *word++;
		done = 1;
		if (is_redir && (*(word - 1) == '<' || *(word - 1) == '>'))
			done = 0;
	}
}

/*
* Goal: Make a new word by replacing ~ by the value of HOME.
*
* Return: The updated word.
*/
static char	*replace_word_tilde(char *word, char *home, int is_redir)
{
	char	*updated_word;
	int		length;

	length = ft_strlen(home);
	updated_word = ft_calloc(length + ft_strlen(word) + 1, sizeof(char));
	if (!updated_word)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (NULL);
	}
	find_and_replace(updated_word, word, home, is_redir);
	return (updated_word);
}

/*
* Goal: Replace all the environement variables in all the TOKEN_CMD tokens
*		from there value in env_local.
*
* Return: 0 on success, 1 on failure.
*/
int	expand_tilde(char ***value, char **env, int is_redir) // could just use **value
{
	int		i;
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
				updated_word = replace_word_tilde((*value)[i], home, is_redir);
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
