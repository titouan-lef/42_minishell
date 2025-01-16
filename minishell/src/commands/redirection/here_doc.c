/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 00:20:34 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/16 02:11:14 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/*
* Goal: Put all the readed lines in the here_doc file until EOF.
*
* Warning: limit must not me null.
*/
static void	get_here_doc_input(int file, char *limit)
{
	int		size_limit;
	char	*line;

	size_limit = ft_strlen(limit);
	while (1)
	{
		ft_putstr("> ");
		line = get_next_line(0);
		if (!line)
		{
			ft_printf_fd(2, "minishell: warning: here-document delimited by end-of-file (wanted '%s')", limit);
			return ;
		}
		if (!ft_strncmp(limit, line, size_limit) && line[size_limit] == '\n')
			break ;
		write(file, line, ft_strlen(line));
		free(line);
	}
	free(line);
}

/*
* Goal: Create a file witha random name.
*
* Warning: limit must not me null.
*/
static t_here_doc	*here_doc(char *limiter)
{
	t_here_doc	*result;

	result = ft_calloc(1, sizeof(t_here_doc));
	if (!result)
	{
		ft_putendl_error("malloc error");
		return (NULL);
	}
	result->limiter = limiter;
	result->filename = generate_random_string(10);
	if (!result->filename)
	{
		free(result);
		return (NULL);
	}
	result->fd = open(result->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (result->fd < 0)
	{
		ft_putendl_error("minishell: here_doc temrorary file has desapered");
		free(result);
		return (NULL);
	}
	get_here_doc_input(result->fd, limiter);
	close(result->fd);
	return (result);
}

static int	process_redir(char *redir, t_list **result)
{
	t_here_doc	*element;
	t_list		*new;

	while (*redir && *(redir + 1) && (*redir != '<' || *(redir + 1) != '<'))
		redir++;
	if (!*redir)
		return (1);
	redir += 2;
	element = here_doc(redir);
	if (!element)
		return (0);
	new = ft_lstnew((void *)element);
	ft_lstadd_back(result, new);
	return (1);
}

t_list	*create_here_docs(t_queue *tokens)
{
	t_list		*result;
	t_token		token;
	t_queue		rebuilt_tokens;
	int			i;

	result = NULL;
	rebuilt_tokens = queue_create();
	while (!queue_is_empty(tokens))
	{
		token = queue_pop(tokens);
		if (token.name == TOKEN_REDIR)
		{
			i = 0;
			while (token.value[i])
			{
				if (!process_redir(token.value[i++], &result))
				{
					token_clear(token);
					queue_clear(&rebuilt_tokens);
					ft_lstclear(&result, NULL);
					return (result);
				}
			}
		}
		if (!queue_push(&rebuilt_tokens, token))
		{
			//token_clear(token);
			queue_clear(&rebuilt_tokens);
			ft_lstclear(&result, NULL);
			return (result);
		}
	}
	//queue_clear(tokens);
	tokens = &rebuilt_tokens;
	return (result);
}

void	clear_here_docs(t_list *here_docs)
{
	while (here_docs)
	{
		unlink(((t_here_doc *)here_docs->content)->filename);
		free(((t_here_doc *)here_docs->content)->filename);
		free(here_docs->content);
		here_docs = here_docs->next;
	}
}
