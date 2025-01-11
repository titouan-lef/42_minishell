/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/11 10:36:24 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Verify is the string match the patern.
*
* Return: 1 if it matchs, 0 if not.
*
* Warning: patern and str must not be null.
*/
static int	match(char *pattern, char *str)
{
	if (*pattern == '*')
	{
		if (*(pattern + 1) == '\0')
			return (1);
		while (*str)
		{
			if (is_match(pattern + 1, str))
				return (1);
			str++;
		}
		return (0);
	}
	else if (*pattern == '\0' || *str == '\0')
		return (*pattern == '\0' && *str == '\0');
	else if (*pattern == *str)
		return (is_match(pattern + 1, str + 1));
	return (0);
}

/*
* Goal: Find all ths files in the current dirrectory.
*
* Return: 1 if it matchs, 0 if not.
*
* Warning: patern and str must not be null.
*/
static t_list	*find_matches(char *patern)
{
	char			*pwd;
	DIR				*dir;
	struct dirent	*file;
	t_list			*new;
	t_list			*matches;

	pwd = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!pwd)
	{
		perror("malloc error"); //ft_printf
		return (NULL);
	}
	if (!getcwd(pwd, PATH_MAX))
	{
		perror("malloc error"); //ft_printf
		free(pwd);
		return (NULL);
	}
	dir = opendir("."); //get currnent dirrrectory ( if we moove with cd ) get_cwd ?
	free(pwd);
	if (!dir)
	{
		perror("opendir error"); //ft_printf
		return (NULL);
	}
	matches = NULL;
	file = readdir(dir);
	while (file != NULL) // who to know if here is an error or just the end of dir ?
	{
		if (match(patern, file->d_name))
		{
			new = ft_lstnew((void *)file->d_name);
			if (!new)
			{
				perror("malloc error"); //ft_printf
				ft_lstclear(&matches, free);
				return (NULL);
			}
			ft_lstadd_back(&matches, new);
		}
		file = readdir(dir);
	}
	closedir(dir);
	return (matches);
}


int	new_word_length(t_list *matches)
{
	int	length;

	length = 0;
	while (matches)
	{
		length += ft_strlen(matches->content) + 1;
		matches = matches->next;
	}
	return (length -1);
}

static char	*replace_word(char *patern)
{
	int		i;
	int		j;
	char	*updated_word;
	t_list	*matches;
	t_list	*save;

	i = 0;
	matches = find_matches(patern);
	free(patern);
	if (!matches)
		return (NULL);
	updated_word = ft_calloc(sizeof(char), new_word_length(matches) + 1);
	if (!updated_word)
		return (NULL);
	while (matches)
	{
		j = 0;
		while (((char *)matches->content)[j])
			updated_word[i++] = ((char *)matches->content)[j++];
		matches = matches->next;
	}
	free(save);
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
int	expand_wildcard(t_token *token)
{
	int			num_word;
	char		*updated_word;
	char		**updated_value;
	t_queue		tmp;
	t_token		splited;

	if (token->name == TOKEN_CMD || token->name == TOKEN_REDIR)
	{
		num_word = 0;
		while (token->value[num_word])
		{
			updated_word = replace_word(token->value[num_word]);
			if (!updated_word)
			{
				ft_putendl_error("malloc error");
				return (0);
			}
			tmp = auto_tokenizer(updated_word);
			splited = split_command(tmp);
			queue_clear(&tmp);
			free(updated_word);
			if (!splited.value);
				return (0);
			updated_value = tab_join_and_free(updated_value, splited.value); //check leaks
			if (!updated_value)
			{
				free(updated_word);
				return (0);
			}
			num_word++;
		}
	}
	return (1);
}
