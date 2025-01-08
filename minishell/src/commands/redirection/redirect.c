/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:54:23 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/08 17:45:20 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (access(file_name, R_OK) == -1)
	{
		ft_putendl_error("Permission denied"); //add minishell: %s, file_name
		return (1);
	}
	fd_file = open(file_name, O_RDONLY);
	if (fd_file == -1)
	{
		ft_putendl_error("No such file or dirrectory"); //add minishell: %s, file_name
		return (1);
	}
	if (dup2(fd_file, fd) == -1)
	{
		ft_putendl_error("dup2 failed");
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
	if (access(file_name, W_OK) == -1)
	{
		ft_putendl_error("Permission denied"); //add minishell: %s, file_name
		return (1);
	}
	fd_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 644);
	if (fd_file == -1)
	{
		ft_putendl_error("No such file or dirrectory"); //add minishell: %s, file_name
		return (1);
	}
	if (dup2(fd_file, fd) == -1)
	{
		ft_putendl_error("dup2 failed");
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
* Warning: file_name must not me null.
*/
int	redirect_output_append_mode(int fd, char *file_name)
{
	int	fd_file;

	if (fd == -1)
		fd = STDIN_FILENO;
	if (access(file_name, W_OK) == -1)
	{
		ft_putendl_error("Permission denied"); //add minishell: %s, file_name
		return (1);
	}
	fd_file = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 644);
	if (fd_file == -1)
	{
		ft_putendl_error("No such file or dirrectory"); //add minishell: %s, file_name
		return (1);
	}
	if (dup2(fd_file, fd) == -1)
	{
		ft_putendl_error("dup2 failed");
		return (1);
	}
	close(fd_file);
	return (0);
}

void	get_here_doc_input(int file, char *limit)
{
	int		size_limit;
	char	*line;

	size_limit = ft_strlen(limit);
	while (1)
	{
		ft_putstr("> "); // as much "pipe" as (b_cmd - 1)
		line = get_next_line(0);
		if (!line)
		{
			ft_printf_fd(2, "minishell: warning: here-document delimited by end-of-file (wanted '%s')", limit); // use of ft_printf_ft
			return ;
		}
		if (!ft_strncmp(limit, line, size_limit) && line[size_limit] == '\n')
			break ;
		write(file, line, ft_strlen(line));
		free(line);
	}
	free(line);
}

int	here_doc(int fd, char *limit)
{
	int		fd_file;
	char	*file_name;

	file_name = ".here_doc"; //randomize name
	fd_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 644);
	if (fd_file < 0)
	{
		ft_putendl_error("No such file or dirrectory"); //add minishell: %s, file_name
		return (1);
	}
	ft_get_here_doc_input(fd_file, limit);
	close(fd_file);
	redirect_input(fd, file_name);
	//pipex->file_in_name = file_name;				//save somewhere to unlink at the end
	return (0);
}
