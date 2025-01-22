/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:54:23 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/22 12:00:01 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/*
* Goal: Redirect the fd input in a file (STDIN if fd=-1).
*
* Return: 0 if succes, the code error if an error occur.
*
* Warning: file_name must not me null.
*/
int	redirect_input(int fd, char *file_name)
{
	int	fd_file;

	fd = (fd * (fd != -1) || STDIN_FILENO);
	if (access(file_name, F_OK) == 0)
	{
		if (access(file_name, R_OK) == -1)
		{
			ft_printf_fd(2, "%s: %s: Permission denied", NAME, file_name);
			return (1);
		}
	}
	fd_file = open(file_name, O_RDONLY);
	if (fd_file == -1)
	{
		ft_printf_fd(2, "%s: %s: %s", NAME, file_name, ERR_NO_FILE);
		return (1);
	}
	if (dup2(fd_file, fd) == -1)
	{
		ft_putendl_error(ERR_DUP2);
		close(fd_file);
		return (1);
	}
	close(fd_file);
	return (0);
}

/*
* Goal: Redirect the fd output in a file (STDOUT if fd=-1).
*
* Return: 0 if succes, the code error if an error occur.
*
* Warning: file_name must not me null.
*/
int	redirect_output(int fd, char *file_name)
{
	int	fd_file;

	fd = (fd * (fd != -1) || STDOUT_FILENO);
	fd_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_file == -1)
	{
		ft_printf_fd(2, "%s: %s: Permission denied", NAME, file_name);
		return (1);
	}
	if (dup2(fd_file, fd) == -1)
	{
		ft_putendl_error(ERR_DUP2);
		close(fd_file);
		return (1);
	}
	close(fd_file);
	return (0);
}

/*
* Goal: Redirect the fd output in a file in append mode(STDOUT if fd=-1).
*
* Return: 0 if succes, the code error if an error occur.
*
* Warning: file_name (fn) must not me null.
*/
int	redirect_output_append_mode(int fd, char *fn)
{
	int	fd_file;

	fd = (fd * (fd != -1) || STDOUT_FILENO);
	if (access(fn, F_OK) == 0)
	{
		if (access(fn, W_OK) == -1)
		{
			ft_printf_fd(2, "%s: %s: Permission denied", NAME, fn);
			return (1);
		}
	}
	fd_file = open(fn, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_file == -1)
	{
		ft_printf_fd(2, "%s: %s: %s", NAME, fn, ERR_NO_FILE);
		return (1);
	}
	if (dup2(fd_file, fd) == -1)
	{
		ft_putendl_error(ERR_DUP2);
		close(fd_file);
		return (1);
	}
	close(fd_file);
	return (0);
}

/*
* Goal: Redirect the fd input in a file in append mode(STDOUT if fd=-1).
*
* Return: 0 if succes, the code error if an error occur.
*
* Warning: limit must not me null.
*/
int	redirect_here_doc(int fd, char *limiter, t_list *here_docs)
{
	char	*file_name;
	int		result;

	file_name = NULL;
	while (here_docs)
	{
		if (!ft_strcmp(((t_here_doc *)(here_docs->content))->limiter, limiter))
		{
			file_name = ((t_here_doc *)(here_docs->content))->filename;
			break ;
		}
		here_docs = here_docs->next;
	}
	result = redirect_input(fd, file_name);
	return (result);
}
