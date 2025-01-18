/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/18 13:50:42 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

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
* Goal: Add to the updated_vlaue the given str.
*
* Return: 1 if errror, 0 if not.
*
* Warning: updated_value and str must not be null.
*/
static int	do_not_replace_word(char ***updated_value, const char *str)
{
	*updated_value = append_to_tab(*updated_value, str);
	if (!updated_value)
	{
		ft_putendl_error("malloc error");
		return (1);
	}
	return (0);
}

/*
* Goal: Add to the updated_vlaue all the find filenames or str if no match.
*
* Return: 1 if errror, 0 if not.
*
* Warning: updated_value and str must not be null.
*/
static int	process_wildcard(char ***updated_value, char *str)
{
	char	*updated_word;

	updated_word = replace_word_wildcard(str);
	if (updated_word)
	{
		if (!update_value(updated_value, updated_word))
			return (1);
	}
	else
		if (do_not_replace_word(updated_value, str))
			return (1);
	return (0);
}

/*
* Goal: Replace all the paterns with correspondings files
		in the current directory.
*
* Return: 1 if errror, 0 if not.
*
* Warning: token must not be null.
*/
int	expand_wildcard(t_token *token) //check speed file creation
{
	int		num_word;
	char	**updated_value;

	if (token->name == TOKEN_CMD || token->name == TOKEN_REDIR)
	{
		num_word = 0;
		updated_value = NULL;
		while (token->value[num_word])
		{
			if (ft_strchr(token->value[num_word], '*'))
			{
				if (process_wildcard(&updated_value, token->value[num_word]))
					return (1);
			}
			else
				if (do_not_replace_word(&updated_value, token->value[num_word]))
					return (1);
			num_word++;
		}
		ft_clean_matrix((void **)token->value);
		token->value = updated_value;
	}
	return (0);
}
