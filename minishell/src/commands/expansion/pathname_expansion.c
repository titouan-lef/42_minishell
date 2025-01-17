/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/17 21:07:09 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Find the new lenght of word arfter pathname expansion.
*
* Return: The length.
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
* Goal: Make a new word with all the file in the current directory
*		that matches with the given patern.
*
* Return: The new word, NULL is case or error.
*
* Warning: patern must not be null.
*/
static char	*replace_word(char *patern)
{
	int		i;
	int		j;
	char	*updated_word;
	t_list	*matches;
	t_list	*save;

	i = 0;
	matches = find_matches(patern);
	if (!matches)
		return (NULL);
	updated_word = ft_calloc(sizeof(char), new_word_length(matches) + 1);
	if (!updated_word)
	{
		ft_putendl_error("malloc error");
		ft_lstclear(&matches, free);
		return (NULL);
	}
	save = matches;
	while (matches)
	{
		j = 0;
		while (((char *)matches->content)[j])
			quote_value(&((char *)matches->content)[j++], updated_word, &i);
		updated_word[i++] = ' ';
		matches = matches->next;
	}
	ft_lstclear(&save, free);
	return (updated_word);
}

/*
* Goal: Add the splited updated word in updated_value.
*
* Return: 1, 0 in case of error.
*
* Warning: updated_value and updated_word must not be null.
*/
static int	update_value(char ***updated_value, char *updated_word)
{
	t_queue	tmp;
	t_token	splited;

	tmp = auto_tokenizer(updated_word);
	free(updated_word);
	splited = split_command(tmp);
	if (splited.value)
	{
		ft_insertion_qsort(splited.value, size_tab(splited.value),
			sizeof(char *), strcmp_lexicographicly);
		*updated_value = tab_join_and_free(*updated_value, splited.value);
		if (!*updated_value)
		{
			ft_putendl_error("malloc error");
			return (0);
		}
	}
	return (1);
}

/*
* Goal: Replace all the paterns with correspondings files in the current directory.
*
* Return: 0 if errror, 1 if not.
*
* Warning: token must not be null.
*/
int	expand_wildcard(t_token *token) //check speed creation
{
	int		num_word;
	char	*updated_word;
	char	**updated_value;

	if (token->name == TOKEN_CMD || token->name == TOKEN_REDIR)
	{
		num_word = 0;
		updated_value = NULL;
		while (token->value[num_word])
		{
			if (ft_strchr(token->value[num_word], '*'))
			{
				updated_word = replace_word(token->value[num_word]);
				if (updated_word)
				{
					if (!update_value(&updated_value, updated_word))
						return (0);
				}
				else
				{
					updated_value = append_to_tab(updated_value, token->value[num_word]);
					if (!updated_value)
					{
						ft_putendl_error("malloc error");
						return (0);
					}
				}
			}
			else
			{
				updated_value = append_to_tab(updated_value, token->value[num_word]);
				if (!updated_value)
				{
					ft_putendl_error("malloc error");
					return (0);
				}
			}
			num_word++;
		}
		ft_clean_matrix((void **)token->value);
		token->value = updated_value;
	}
	return (1);
}
