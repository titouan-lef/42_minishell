/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/18 13:40:16 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Find the new lenght of word arfter pathname expansion.
*
* Return: The length.
*
* Warning: mathces must not be null.
*/
static int	new_word_length(t_list *matches)
{
	int	length;

	length = 0;
	while (matches)
	{
		length += value_length_quoted(matches->content) + 1;
		matches = matches->next;
	}
	return (length);
}

/*
* Goal: Add all the match filnames in the new word separated by a space.
*
* Warning: updated_word, mathces and i must not be null.
*/
static void	rebuilt_word(char *updated_word, t_list *matches, int *i)
{
	int	j;

	while (matches)
	{
		j = 0;
		while (((char *)matches->content)[j])
			quote_value(&((char *)matches->content)[j++], updated_word, i);
		if (matches->next)
			updated_word[(*i)++] = ' ';
		matches = matches->next;
	}
}

/*
* Goal: Make a new word with all the file in the current directory
*		that matches with the given patern.
*
* Return: The new word, NULL is case or error.
*
* Warning: patern must not be null.
*/
char	*replace_word_wildcard(char *patern)
{
	int		i;
	char	*updated_word;
	t_list	*matches;

	i = 0;
	matches = find_matches(patern);
	if (!matches)
		return (NULL);
	updated_word = ft_calloc(sizeof(char), new_word_length(matches));
	if (!updated_word)
	{
		ft_putendl_error("malloc error");
		ft_lstclear(&matches, free);
		return (NULL);
	}
	rebuilt_word(updated_word, matches, &i);
	ft_lstclear(&matches, free);
	return (updated_word);
}
