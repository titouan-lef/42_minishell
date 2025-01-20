/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 00:20:34 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/20 16:28:09 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/*
* Goal: Replace env var if needed and write the line in the file.
*
* Return: 0 if succed, 1 if not.
*
* Warning: limit, line and env must not me null.
*/
static int	write_and_free(int file, char *limiter, char *line, char **env)
{
	char	*tmp;

	if (!ft_strchr(limiter, '\'') && !ft_strchr(limiter, '\"'))
	{
		tmp = replace_word_env(line, env, 1);
		if (!tmp)
		{
			ft_printf_fd(2, "%s: %s", NAME, MALLOC);
			free(line);
			return (1);
		}
		free(line);
		line = tmp;
	}
	if (write(file, line, ft_strlen(line)) == -1)
	{
		ft_printf_fd(2, "%s: %s", NAME, HERDOC_ACC);
		free(line);
		return (1);
	}
	free(line);
	return (0);
}

/*
* Goal: Read the input and writes it in the file.
*
* Return: 0 if succed, 1 if not or -1 the limiter is detected
*
* Warning: limiters and env must not me null.
*/
static int	process_line(int file, char *limiter,
			char *unquoted_limiter, char **env)
{
	char	*line;
	int		limiter_length;

	limiter_length = ft_strlen(unquoted_limiter);
	ft_putstr("> ");
	line = get_next_line(0);
	if (!line)
	{
		ft_printf_fd(2, "%s: %s (wanted '%s')",
			NAME, HERDOC_END, unquoted_limiter);
		free(unquoted_limiter);
		return (1);
	}
	if (!ft_strncmp(unquoted_limiter, line, limiter_length)
		&& line[limiter_length] == '\n')
	{
		free(line);
		return (-1);
	}
	if (write_and_free(file, limiter, line, env))
		return (1);
	return (0);
}

/*
* Goal: Put all the readed lines in the here_doc file until EOF.
*
* Return: 0 if succed, 1 if not.
*
* Warning: limit and env must not me null.
*/
int	get_here_doc_input(int file, char *limiter, char **env)
{
	char	*unquoted_limiter;
	int		result;

	unquoted_limiter = replace_word_quotes(limiter);
	if (!unquoted_limiter)
		return (1);
	while (1)
	{
		result = process_line(file, limiter, unquoted_limiter, env);
		if (result == -1)
			break ;
		if (result)
		{
			free(unquoted_limiter);
			return (1);
		}
	}
	free(unquoted_limiter);
	return (0);
}
