/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/30 16:19:31 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Copy word in updated word untill the next quote '.
*
* Warning: word, updated_word and letter must not be null.
*/
static int	update_quote(char **word, char *updated_word, int letter)
{
	updated_word[letter++] = *(*word)++;
	while (**word != '\'')
		updated_word[letter++] = *(*word)++;
	updated_word[letter++] = *(*word)++;
	return (letter);
}

static int	do_not_replace(char *updated_word, char *word,
	int letter, int condition)
{
	if (condition && ft_strncmp(word, "<<", 2) == 0) //strchr
	{
		ft_strlcpy(updated_word + letter, word, ft_strlen(word) + 1);
		return (1);
	}
	return (0);
}

/*
* Goal: Make a new word with all the environement variables
*		in the given word from there value in env.
*
* Return: The updated word.
*
* Warning: word and env must not be null.
*/
char	*replace_word_env(char *word, char **env, int here_doc, int redir)
{
	int		letter;
	char	*updated_word;
	int		in_double_quotes;

	letter = 0;
	in_double_quotes = 0;
	updated_word = ft_calloc(new_word_lenght(word, env) + 1, sizeof(char));
	while (updated_word && *word)
	{
		if (do_not_replace(updated_word, word, letter, !here_doc && redir))
			break ;
		if (*word == '"')
			in_double_quotes = !in_double_quotes;
		if (*word == '$' && (*(word + 1) == '\'' || *(word + 1) == '\"')
			&& !in_double_quotes)
			word++;
		else if (*word == '$')
			update_env_var(&word, updated_word, &letter, env);
		else if (!here_doc && *word == '\'' && !in_double_quotes)
			letter = update_quote(&word, updated_word, letter);
		else
			updated_word[letter++] = *word++;
	}
	return (updated_word);
}

/*
* Goal: Make a new word with all the environement variables
*		in the given word from there value in env_local.
*
* Return: The updated word.
*
* Warning: word and env_local must not be null.
*/
static char	**update_value(char **updated_value, char *updated_word, char *name, int is_redir)
{
	t_queue	tmp;
	t_token	splited;

	tmp = tokenizer(updated_word);
	free(updated_word);
	splited = split_command(tmp);
	if (is_redir && splited.value && splited.value[0] && splited.value[1])
	{
		token_clear(splited);
		ft_printf_fd(2, "%s: %s: ambiguous redirect\n", NAME, name);
		updated_value = append_to_tab(updated_value, "");
	}
	else if (splited.value)
		updated_value = tab_join_and_free(updated_value, splited.value);
	if (!updated_value)
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
	return (updated_value);
}

/*
* Goal: Replace all the environement variables in all the TOKEN_CMD tokens
*		from there value in env_local.
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
		updated_value = update_value(updated_value, updated_word, (*value)[i++], is_redir);
		if (!updated_value)
			return (1);
	}
	ft_clean_matrix((void **)*value);
	*value = updated_value;
	return (0);
}
