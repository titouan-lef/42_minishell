/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 00:20:34 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/06 10:10:11 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "redir.h"

/*
* Goal: Replace env var if needed and write the line in the file.
*
* Return: 0 if succed, 1 if not.
*
* Warning: limit, line and env must not me null.
*/
static int	write_and_free(int file, char *limiter, char *line, t_data *data)
{
	char	*old;
	int		result;

	if (!ft_strchr(limiter, '\'') && !ft_strchr(limiter, '\"'))
	{
		line = replace_word_env(line, data->env, 1, 0);
		if (!line)
		{
			ft_printf_fd(2, "%s: %s", NAME, ERR_MALLOC);
			return (1);
		}
		old = line;
		line = replace_word_exit(line, data->last_exit);
		free(old);
		if (!line)
		{
			ft_printf_fd(2, "%s: %s", NAME, ERR_MALLOC);
			return (1);
		}
		result = ft_putendl_fd(line, file);
		free(line);
	}
	else
		result = ft_putendl_fd(line, file);
	if (result == -1)
	{
		ft_printf_fd(2, "%s: %s", NAME, ERR_HERDOC_ACC);
		return (1);
	}
	return (0);
}

static int	event(void)
{
	return 0;// pas sure qu'on garde.
}

/*
* Goal: Read the input and writes it in the file.
*
* Return: 0 if succed, 1 if not or -1 the limiter is detected
*
* Warning: limiters and env must not me null.
*/
static int	process_line(int file, char *limiter,
			char *unquoted_limiter, t_data *data)
{
	char	*line;
	int		limiter_length;
	int		code;

	limiter_length = ft_strlen(unquoted_limiter);
	rl_event_hook = event;
	line = read_lines(data, 1);
	rl_event_hook = 0;
	code = get_signal_receive();
	if (!line || code)
	{
		if (code)
			return (code);
		ft_printf_fd(2, "%s: %s (wanted `%s')\n",
			NAME, ERR_HERDOC_END, unquoted_limiter);
		return (-1);
	}
	if (!ft_strcmp(unquoted_limiter, line))
		return (-1);
	if (write_and_free(file, limiter, line, data))
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
static int	get_here_doc_input(int file, char **limiter, t_data *data)
{
	char	*unquoted_limiter;
	int		result;

	unquoted_limiter = replace_word_quotes(*limiter);
	if (!unquoted_limiter)
		return (1);
	while (1)
	{
		result = process_line(file, *limiter, unquoted_limiter, data);
		if (result == -1)
			break ;
		if (result)
		{
			free(unquoted_limiter);
			return (result);
		}
	}
	free(*limiter);
	*limiter = unquoted_limiter;
	return (0);
}

/*
* Goal: Create a file with a random name.
*
* Return: 0 if succed, 1 if not.
*/
int	read_here_docs(t_data *data)
{
	t_list		*here_docs;
	t_here_doc	*here_doc;
	int			fd;
	int			result;

	here_docs = data->lst;
	while (here_docs)
	{
		here_doc = here_docs->content;
		here_doc->filename = generate_random_string(10);
		if (!here_doc->filename)
			return (1);
		fd = open(here_doc->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			ft_printf_fd(2, "%s: %s", NAME, ERR_HERDOC_ACC);
			return (1);
		}
		result = get_here_doc_input(fd, &here_doc->limiter, data);
		close(fd);
		if (result)
			return (result);
		here_docs = here_docs->next;
	}
	return (0);
}
