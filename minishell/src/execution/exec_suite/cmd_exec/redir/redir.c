/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:49:39 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/10 16:56:33 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
* Goal: Identify the type of redirection.
*
* Return: The enum redir name.
*/
static int	choose_redir(char *redir)
{
	if (!*redir)
		return (ERROR);
	if (*redir == '<')
	{
		if (*(redir + 1) == '<')
			return (HERE_DOC);
		return (INPUT);
	}
	if (*(redir + 1) == '>')
		return (OUTPUT_APPEND);
	return (OUTPUT);
}

/*
* Goal: Find id in the redir.
*
* Return: The fd found, -1 if not.
*/
static int	find_fd(char **redir)
{
	int		fd;

	fd = -1;
	if (ft_isdigit(**redir))
		fd = ft_atoi(*redir);
	while (ft_isdigit(**redir))
		(*redir)++;
	return (fd);
}

/*
* Goal: Redirect output or input with the given redirection.
*
* Return: O on success, or the error code corresponding.
*/
int	redir_manager(char **redirs, t_list *here_docs)
{
	int		i;
	int		fd;
	int		result;
	char	*redir;

	if (!redirs)
		return (0);
	i = 0;
	result = 0;
	while (redirs[i] && !result)
	{
		redir = redirs[i++];
		fd = find_fd(&redir);
		if (choose_redir(redir) == INPUT)
			result = redirect_input(fd, redir + 1);
		else if (choose_redir(redir) == HERE_DOC)
			result = redirect_here_doc(fd, redir + 2, here_docs);
		else if (choose_redir(redir) == OUTPUT)
			result = redirect_output(fd, redir + 1);
		else if (choose_redir(redir) == OUTPUT_APPEND)
			result = redirect_output_append_mode(fd, redir + 2);
		else
			return (1);
	}
	return (result);
}
