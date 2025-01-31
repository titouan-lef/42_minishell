/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:49:39 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/31 11:52:29 by lguerbig         ###   ########.fr       */
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
	int		result;

	if (!redirs)
		return (0);
	i = 0;
	result = 0;
	while (redirs[i] && !result)
	{
		fd = find_fd(&redirs[i]);
		if (choose_redir(redirs[i]) == INPUT)
			result = redirect_input(fd, redirs[i] + 1);
		else if (choose_redir(redirs[i]) == HERE_DOC)
			result = redirect_here_doc(fd, redirs[i] + 2, here_docs);
		else if (choose_redir(redirs[i]) == OUTPUT)
			result = redirect_output(fd, redirs[i] + 1);
		else if (choose_redir(redirs[i]) == OUTPUT_APPEND)
			result = redirect_output_append_mode(fd, redirs[i] + 2);
		else
			return (1);
		i++;
	}
	return (result);
}
