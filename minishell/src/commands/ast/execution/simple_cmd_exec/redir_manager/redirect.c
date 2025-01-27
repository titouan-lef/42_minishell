/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:54:23 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/24 14:38:45 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static int	check_perm(char *file_name)
{
	if (access(file_name, F_OK) == 0)
	{
		if (access(file_name, R_OK) == -1)
		{
			ft_printf_fd(2, "%s: %s: Permission denied\n", NAME, file_name);
			return (1);
		}
	}
	return (0);
}

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

	if (fd == -1)
		fd = STDIN_FILENO;
	if (check_perm(file_name))
		return (1);
	fd_file = open(file_name, O_RDONLY);
	if (fd_file == -1)
	{
		ft_printf_fd(2, "%s: %s: %s\n", NAME, file_name, ERR_NO_FILE);
		return (1);
	}
	if (dup2(fd_file, fd) == -1)
	{
		ft_printf_fd(2, "%s: %s", NAME, ERR_DUP2);
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

	if (fd == -1)
		fd = STDOUT_FILENO;
	fd_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_file == -1)
	{
		ft_printf_fd(2, "%s: %s: Permission denied\n", NAME, file_name);
		return (1);
	}
	if (dup2(fd_file, fd) == -1)
	{
		ft_printf_fd(2, "%s: %s", NAME, ERR_DUP2);
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
int	redirect_output_append_mode(int fd, char *file_name)
{
	int	fd_file;

	if (fd == -1)
		fd = STDOUT_FILENO;
	fd_file = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_file == -1)
	{
		ft_printf_fd(2, "%s: %s: Permission denied\n", NAME, file_name);
		return (1);
	}
	if (dup2(fd_file, fd) == -1)
	{
		ft_printf_fd(2, "%s: %s", NAME, ERR_DUP2);
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
