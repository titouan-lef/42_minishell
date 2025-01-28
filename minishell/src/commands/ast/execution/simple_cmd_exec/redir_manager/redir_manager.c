/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:49:39 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/28 16:00:41 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/*
* Goal: Identify the type of redirection.
*
* Return: the enum redir name.
*
* Warning: redir must not me null.
*/
static int	choose_redir(char *redir)
{
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
* Return: The fd found, -1 if no fd.
*
* Warning: redir must not me null.
*/
static int	find_fd(char **redir)
{
	int	fd;

	fd = -1;
	if (ft_isdigit(**redir))
		fd = ft_atoi(*redir);
	while (ft_isdigit(**redir))
		(*redir)++;
	return (fd);
}

/*
* Goal: Redirect the output or input with the given redirection.
*
* Return: 0 if succes, the code error if an error occur.
*
* Warning: token.value must not me null.
*/
int	redir_manager(char **redirs, t_list *here_docs)
{
	int		i;
	int		fd;
	int		code_error;
	char	*redir;

	if (!redirs)
		return (0);
	i = 0;
	redir = redirs[i];
	while (redir)
	{
		fd = find_fd(&redir);
		if (choose_redir(redir) == INPUT)
			code_error = redirect_input(fd, redir + 1);
		else if (choose_redir(redir) == HERE_DOC)
			code_error = redirect_here_doc(fd, redir + 2, here_docs);
		else if (choose_redir(redir) == OUTPUT)
			code_error = redirect_output(fd, redir + 1);
		else
			code_error = redirect_output_append_mode(fd, redir + 2);
		if (code_error)
			return (code_error);
		redir = redirs[++i];
	}
	return (0);
}
