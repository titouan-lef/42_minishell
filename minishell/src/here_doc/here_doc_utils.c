/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 00:20:34 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/12 15:42:19 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

/*
* Goal: Fill the random_string with random characteres.
*/
static void	fill_str(char *random_string, int fd, size_t length)
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
* Goal: Generate a random string of alpha numeric characters.
*
* Return: The generated string, NULL if malloc error.
*/
char	*generate_random_string(size_t length)
{
	int		fd;
	char	*random_string;

	random_string = (char *)ft_calloc((length + 1), sizeof(char));
	if (!random_string)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (NULL);
	}
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
* Goal: Read here doc and add file name in data list.
*
* Return: 0 on success, 1 on failure.
*/
static int	process_here_doc(char **redir, char *limiter, t_data *data)
{
	char	*filename;
	int		result;
	t_list	*new;
	char	*tmp;

	result = read_here_doc(limiter, &filename, data);
	if (result)
		return (result);
	new = ft_lstnew(filename);
	if (!new)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		free(filename);
		return (1);
	}
	ft_lstadd_back(&data->here_docs, new);
	tmp = ft_strjoin("<", filename);
	if (!tmp)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (1);
	}
	free(*redir);
	*redir = tmp;
	return (0);
}

/*
* Goal: Process each here doc found and detects error syntaxes in 'redirs'.
* Index of redir that have a syntax error is define in 'i'.
*
* Return: 0 on succes or the code error corresponding (2 is syntax error).
*/
int	fill_here_doc_lst(char **redirs, t_data *data, int *i)
{
	char	*redir;
	int		result;

	if (!redirs)
		return (0);
	*i = 0;
	while (redirs[*i])
	{
		redir = redirs[*i];
		while (redir[0] != '<' && redir[0] != '>')
			redir++;
		if (!redir[1] || ((redir[1] == '<' || redir[1] == '>') && !redir[2]))
			return (2);
		if (redir[0] == '<' && redir[1] == '<')
		{
			if (redir[0] == '\0')
				return (2);
			result = process_here_doc(redirs + *i, redir + 2, data);
			if (result)
				return (result);
		}
		*i += 1;
	}
	return (0);
}

/*
* Goal: Clear the list of heredocs filename.
*/
void	clear_here_docs(t_list *here_docs)
{
	char	*filename;

	while (here_docs)
	{
		filename = (char *)here_docs->content;
		if (filename)
			unlink(filename);
		here_docs = ft_lstremove_front(here_docs, free);
	}
}
