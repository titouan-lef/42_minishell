/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 00:20:34 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/05 17:42:06 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static void	fill_str(char *random_string, int fd, size_t length)//if norm problem --> rand_str.c
{
	char	random_char;
	size_t	i;

	i = 0;
	while (i < length)
	{
		if (read(fd, &random_char, 1) != 1)
		{
			ft_printf_fd(2, "%s: %s\n", NAME, ERR_RND);
			free(random_string);
			random_string = NULL;
			break ;
		}
		if (ft_isalnum(random_char))
			random_string[i++] = random_char;
	}
}

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
* Goal: Generate a random string of alpha numeric characters.
*
* Return: The generated string.
*/
char	*generate_random_string(size_t length)//if norm problem --> rand_str.c
{
	int		fd;
	char	*random_string;

	random_string = (char *)ft_calloc((length + 1), sizeof(char));
	if (!random_string)
		return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_RND);
		free(random_string);
		return (NULL);
	}
	fill_str(random_string, fd, length);
	close(fd);
	return (random_string);
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

/*
* Goal: Add each here_doc found in the list
*		and detects errors syntaxes in redirections.
*
* Return: -1 if succed, -2 if malloc error or the index of
*			the element in redir that have a syntax error.
*
* Warning: redirs and here_docs must not me null.
*/
int	fill_here_doc_lst(char **redirs, t_list **here_docs)
{
	t_list	*new;
	char	*redir;
	int		i;

	if (!redirs)
		return (-1);
	i = 0;
	while (redirs[i])
	{
		redir = redirs[i++];
		while (redir[0] != '<' && redir[0] != '>')
			redir++;
		if (!redir[1] || ((redir[1] == '<' || redir[1] == '>') && !redir[2]))
			return (i - 1);
		if (redir[0] != '<' || redir[1] != '<')
			continue ;
		redir += 2;
		if (redir[0] == '\0')
			return (i - 1);
		new = new_here_doc(redir);
		if (!new)
			return (-2);
		ft_lstadd_back(here_docs, new);
	}
	return (-1);
}
