/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:49:39 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/09 14:00:44 by lguerbig         ###   ########.fr       */
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
	int		fd;

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
int	make_redirs(t_token token_redir)
{
	int		i;
	int		fd;
	int		code_error;
	char	*redir;

	i = 0;
	redir = token_redir.value[i];
	while (redir)
	{
		fd = find_fd(&redir);
		if (choose_redir(redir) == INPUT)
			code_error = redirect_input(fd, redir + 1);
		else if (choose_redir(redir) == HERE_DOC)
			code_error = here_doc(fd, redir + 2);
		else if (choose_redir(redir) == OUTPUT)
			code_error = redirirect_output(fd, redir + 1);
		else
			code_error = redirect_output_append_mode(fd, redir + 2);
		if (code_error)
			return (code_error);
		redir = token_redir.value[++i];
	}
	return (0);
}
