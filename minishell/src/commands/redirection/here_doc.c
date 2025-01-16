/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 00:20:34 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/16 20:32:52 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/*
* Goal: Put all the readed lines in the here_doc file until EOF.
*
* Warning: limit must not me null.
*/
static int	get_here_doc_input(int file, char *limiter)
{
	int		size_limit;
	char	*line;

	size_limit = ft_strlen(limiter);
	while (1)
	{
		ft_putstr("> ");
		line = get_next_line(0);
		if (!line)
		{
			ft_printf_fd(2, "minishell: warning: here-document delimited by end-of-file (wanted '%s')", limiter);
			return (1);
		}
		if (!ft_strncmp(limiter, line, size_limit) && line[size_limit] == '\n')
			break ;
		if (write(file, line, ft_strlen(line)) == -1)
		{
			ft_printf_fd(2, "minishell: error here_doc access");
			free(line);
			return (1);
		}
		free(line);
	}
	free(line);
	return (0);
}

/*
* Goal: Create a file witha random name.
*
* Warning: limit must not me null.
*/
int	read_here_docs(t_list *here_docs)
{
	t_here_doc	*here_doc;
	int			fd;

	while (here_docs)
	{
		here_doc = here_docs->content;
		here_doc->filename = generate_random_string(10);
		if (!here_doc->filename)
			return (1);
		fd = open(here_doc->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			ft_putendl_error("minishell: error here_doc access");
			return (1);
		}
		if (get_here_doc_input(fd, here_doc->limiter))
		{
			close(fd);
			return (1);
		}
		close(fd);
		here_docs = here_docs->next;
	}
	return (0);
}

/*
* Goal: Create a file witha random name.
*
* Warning: limit must not me null.
*/
static t_here_doc	*new_here_doc(char *limiter)
{
	t_here_doc	*result;

	result = ft_calloc(1, sizeof(t_here_doc));
	if (!result)
	{
		ft_putendl_error("malloc error");
		return (NULL);
	}
	result->limiter = limiter;
	return (result);
}

int	detect_here_docs(t_token token, t_list **here_docs)
{
	t_here_doc	*element;
	t_list		*new;
	char		*redir;
	int			i;

	i = 0;
	while (token.value[i])
	{
		redir = token.value[i];
		i++;
		while (*redir && *(redir + 1) && (*redir != '<' || *(redir + 1) != '<'))
			redir++;
		if (!*redir)
			continue ;
		redir += 2;
		element = new_here_doc(redir);
		if (!element)
			return (1);
		new = ft_lstnew(element);
		if (!new)
		{
			free(element);
			return (1);
		}
		ft_lstadd_back(here_docs, new);
	}
	return (0);
}

void	clear_here_docs(t_list *here_docs)
{
	while (here_docs)
	{
		unlink(((t_here_doc *)here_docs->content)->filename);
		free(((t_here_doc *)here_docs->content)->filename);
		here_docs = ft_lstremove_front(here_docs, free);
	}
}
