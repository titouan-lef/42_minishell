/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/06 17:06:11 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "lexer.h"

/*
* Goal: Split updated_value on whitespace and rebuilt the command.
*
* Return: 1, 0 in case of error.
*
* Warning: updated_value and updated_word must not be null.
*/
static int	update_value(char ***updated_value, char *updated_word,
	char *patern, int is_redir)
{
	t_queue	tmp;
	t_token	splited;

	if (lexer(updated_word, &tmp))
		return (1);
	free(updated_word);
	splited = split_command(tmp);
	if (is_redir && splited.value && splited.value[0] && splited.value[1])
	{
		token_clear(splited);
		ft_printf_fd(2, "%s: %s: ambiguous redirect\n", NAME, patern);
		*updated_value = append_to_tab(*updated_value, "");
	}
	else if (splited.value)
	{
		ft_insertion_qsort(splited.value, size_tab(splited.value),
			sizeof(char *), strcmp_lexicographicly);
		*updated_value = tab_join_and_free(*updated_value, splited.value);
	}
	if (!*updated_value)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (0);
	}
	return (1);
}

/*
* Goal: Add to the updated_vlaue the given patern.
*
* Return: 1 if errror, 0 if not.
*
* Warning: updated_value and patern must not be null.
*/
static int	do_not_replace_word(char ***updated_value, const char *patern)
{
	*updated_value = append_to_tab(*updated_value, patern);
	if (!updated_value)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (1);
	}
	return (0);
}

/*
* Goal: Add to the updated_value all the find filenames or patern if no match.
*
* Return: 1 if errror, 0 if not.
*
* Warning: updated_value and patern must not be null.
*/
static int	process_wildcard(char ***updated_value, char *patern, int is_redir)
{
	char	*updated_word;
	char	*name;
	int		result;

	name = patern;
	if (is_redir)
	{
		while (*name != '>' && *name != '<')
			name++;
		if (ft_strncmp(name, "<<", 2) == 0)
		{
			result = do_not_replace_word(updated_value, patern);
			return (result);
		}
		while (*name == '>' || *name == '<')
			name++;
	}
	updated_word = replace_word_wildcard(name);
	if (updated_word)
		result = !update_value(updated_value, updated_word, name, is_redir);
	else
		result = do_not_replace_word(updated_value, patern);
	return (result);
}

/*
* Goal: Replace all the paterns with correspondings files
		in the current directory.
*
* Return: 1 if errror, 0 if not.
*
* Warning: token must not be null.
*/
int	expand_wildcard(char ***value, int is_redir) //check speed file creation
{
	int		num_word;
	char	**updated_value;

	num_word = 0;
	updated_value = NULL;
	while ((*value)[num_word])
	{
		if (ft_strchr((*value)[num_word], '*'))
		{
			if (process_wildcard(&updated_value, (*value)[num_word], is_redir))
				return (1);
		}
		else if (do_not_replace_word(&updated_value, (*value)[num_word]))
			return (1);
		num_word++;
	}
	ft_clean_matrix((void **)*value);
	*value = updated_value;
	return (0);
}
