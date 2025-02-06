/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/06 10:25:04 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Split the new word on whitespace and rebuilt the command.
*
* Return: 1 if error malloc, 0 if not.
*
* Warning: updated_value, updated_word and name must not be null.
*/
static int	update_value(char ***updated_value, char *updated_word
	, char *name, int is_redir)
{
	t_queue	tmp;
	t_token	splited;
	int		result;

	result = lexer(updated_word, &tmp);
	if (result)
		return (result);
	free(updated_word);
	splited = split_command(tmp);
	if (!splited.value)
		return (0);
	else if (is_redir && splited.value && splited.value[0] && splited.value[1])
	{
		token_clear(splited);
		ft_printf_fd(2, "%s: %s: ambiguous redirect\n", NAME, name);
		*updated_value = append_to_tab(*updated_value, "");
	}
	else
		*updated_value = tab_join_and_free(*updated_value, splited.value);
	if (!*updated_value)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (1);
	}
	return (0);
}

/*
* Goal: Replace all the environement variables in the hole command
*		from there value in env.
*
* Return: 1 if errror, 0 if not.
*
* Warning: token and env_local must not be null.
*/
int	expand_env_var(char ***value, char **env, int is_redir)
{
	int		i;
	char	*updated_word;
	char	**updated_value;

	updated_value = NULL;
	i = 0;
	while ((*value)[i])
	{
		updated_word = replace_word_env((*value)[i], env, 0, is_redir);
		if (!updated_word)
		{
			ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
			return (1);
		}
		if (update_value(&updated_value, updated_word, (*value)[i++], is_redir))
			return (1);
	}
	ft_clean_matrix((void **)*value);
	*value = updated_value;
	return (0);
}
