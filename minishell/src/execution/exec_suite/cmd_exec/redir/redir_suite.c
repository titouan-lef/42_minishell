/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_suite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:54:23 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/10 19:13:28 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "here_doc.h"

static void	print_error_open(char *file_name)
{
	if (access(file_name, F_OK) == 0)
		ft_printf_fd(2, "%s: %s: %s\n", NAME, file_name, ERR_NO_PERM);
	else
		ft_printf_fd(2, "%s: %s: %s\n", NAME, file_name, ERR_NO_FILE);
}

/*
* Goal: Redirects the file out to fd for reading (STDIN if fd=-1).
*
* Return: O on success, or the error code corresponding.
*/
int	redirect_input(int fd, char *file_name)
{
	int	fd_file;

	if (fd == -1)
		fd = STDIN_FILENO;
	if (access(file_name, F_OK) == 0 && access(file_name, R_OK) == -1)
	{
		ft_printf_fd(2, "%s: %s: %s\n", NAME, file_name, ERR_NO_PERM);
		return (1);
	}
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
* Goal: Redirects the file to fd for writting (STDOUT if fd=-1).
*
* Return: O on success, or the error code corresponding.
*/
int	redirect_output(int fd, char *file_name)
{
	int			fd_file;
	struct stat	infos;

	if (fd == -1)
		fd = STDOUT_FILENO;
	if (stat(file_name, &infos) == 0 && S_ISDIR(infos.st_mode))
	{
		ft_printf_fd(2, "%s: %s: Is a directory\n", NAME, file_name);
		return (1);
	}
	fd_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_file == -1)
	{
		print_error_open(file_name);
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
* Goal: Redirects the file to fd for appending (STDOUT if fd=-1).
*
* Return: O on success, or the error code corresponding.
*
* Warning: file_name (fn) must not me null.
*/
int	redirect_output_append_mode(int fd, char *file_name)
{
	int			fd_file;
	struct stat	infos;

	if (fd == -1)
		fd = STDOUT_FILENO;
	if (stat(file_name, &infos) == 0 && S_ISDIR(infos.st_mode))
	{
		ft_printf_fd(2, "%s: %s: Is a directory\n", NAME, file_name);
		return (1);
	}
	fd_file = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_file == -1)
	{
		print_error_open(file_name);
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
* Goal: Redirects the heredoc to fd for reading (STDOUT if fd=-1).
*
* Return: O on success, or the error code corresponding.
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
