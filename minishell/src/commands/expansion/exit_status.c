/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/28 16:18:01 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Make a new word with all the environement variables
*		in the given word from there value in env_local.
*
* Return: The updated word.
*
* Warning: word and env_local must not be null.
*/
static char	*replace_word_exit(char *word, int last_exit)
{
	int		letter;
	char	*updated_word;
	char	*exit_status;
	int		length;

	exit_status = ft_itoa(last_exit);
	length = ft_strlen(exit_status);
	if (!exit_status)
		return (NULL);
	updated_word = ft_calloc(length + ft_strlen(word) + 1, sizeof(char));
	letter = 0;
	while (updated_word && *word)
	{
		if (*(word + 1) && *word == '$' && *(word + 1) == '?')
		{
			ft_strlcpy(updated_word + letter, exit_status, length + 1);
			letter += length;
			word += 2;
		}
		else
			updated_word[letter++] = *word++;
	}
	free(exit_status);
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
int	expand_exit_status(char ***value, int last_exit)
{
	int		i;
	char	*updated_word;

	i = 0;
	while ((*value)[i])
	{
		if (ft_strnstr((*value)[i], "$?", ft_strlen((*value)[i])))
		{
			updated_word = replace_word_exit((*value)[i], last_exit);
			if (!updated_word)
			{
				ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
				return (1);
			}
			free((*value)[i]);
			(*value)[i] = updated_word;
		}
		i++;
	}
	return (0);
}
