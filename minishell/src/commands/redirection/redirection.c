/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:49:39 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/08 13:18:49 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

typedef enum e_redir_name
{
	INPUT,
	HERE_DOC,
	OUTPUT,
	OUTPUT_APPEND,
}			t_redir_name;

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
* Goal: Identify the type of redirection.
*
* Return: The fd found.
*
* Warning: redir must not me null.
*/
static int	find_fd_if_precised(char **redir)
{
	int		fd;

	fd = -1;
	if (ft_isdigit(**redir))
		fd = ft_atoi(*redir);
	while (ft_isdigit(**redir))
		(*redir)++;
	return (fd);
}

int	make_redirs(t_token token_redir)
{
	int		i;
	int		fd;
	char	*redir;

	i = 0;
	redir = token_redir.value[i];
	while (redir)
	{
		fd = find_fd_if_precised(&redir);
		if (choose_redir(redir) == INPUT)
			if (!redirect_intput(fd, redir + 1))
				return (0);
		if (choose_redir(redir) == HERE_DOC)
			if (!here_doc(fd, redir + 2))
				return (0);
		if (choose_redir(redir) == OUTPUT)
			if (!redir_output(fd, redir + 1))
				return (0);
		if (choose_redir(redir) == OUTPUT_APPEND)
			if (!redir_output_append_mode(fd, redir + 2))
				return (0);
		redir = token_redir.value[++i];
	}
	return (1);
}
