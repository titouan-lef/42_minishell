/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 00:20:34 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/22 12:02:37 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/*
* Goal: Create a new node of struct here_doc with the given limiter.
*
* Return: The here_doc struct, NULL if error.
*
* Warning: limit must not me null.
*/
static t_list	*new_here_doc(char *limiter)
{
	t_list		*new;
	t_here_doc	*element;

	element = ft_calloc(1, sizeof(t_here_doc));
	if (!element)
	{
		ft_printf_fd(2, "%s: %s", NAME, ERR_MALLOC);
		return (NULL);
	}
	element->limiter = ft_strdup(limiter);
	if (!element)
	{
		ft_printf_fd(2, "%s: %s", NAME, ERR_MALLOC);
		free(element);
		return (NULL);
	}
	new = ft_lstnew(element);
	if (!new)
	{
		clear_here_docs(new);
		return (NULL);
	}
	return (new);
}

/*
* Goal: Add each here_dc found in the list.
*
* Return: 1 if succed, 0 if not.
*
* Warning: limit must not me null.
*/
int	detect_here_docs(t_token token, t_list **here_docs)
{
	t_list		*new;
	char		*redir;
	int			i;

	i = 0;
	while (token.value[i])
	{
		redir = token.value[i++];
		while (*(redir + 1) && (*redir != '<' || *(redir + 1) != '<'))
			redir++;
		if (!*(redir + 1))
			continue ;
		redir += 2;
		new = new_here_doc(redir);
		if (!new)
			return (1);
		ft_lstadd_back(here_docs, new);
	}
	return (0);
}

/*
* Goal: Create a file witha random name.
*
* Return: 1 if succed, 0 if not.
*/
int	read_here_docs(t_list *here_docs, char **env)
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
			ft_printf_fd(2, "%s: %s", NAME, ERR_HERDOC_ACC);
			return (1);
		}
		if (get_here_doc_input(fd, here_doc->limiter, env))
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
* Goal: Clear the list of here_doc struct.
*
* Warning: here_docs must not me null.
*/
void	clear_here_docs(t_list *here_docs)
{
	while (here_docs)
	{
		unlink(((t_here_doc *)here_docs->content)->filename);
		free(((t_here_doc *)here_docs->content)->filename);
		free(((t_here_doc *)here_docs->content)->limiter);
		here_docs = ft_lstremove_front(here_docs, free);
	}
}
