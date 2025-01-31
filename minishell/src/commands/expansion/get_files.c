/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:30:28 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/31 10:56:53 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Verify is the string match the patern.
*
* Return: 1 if it matchs, 0 if not.
*
* Warning: patern and str must not be null.
*/
static int	match(char *pattern, char *str)
{
	if (*pattern == '*')
	{
		if (*(pattern + 1) == '\0')
			return (1);
		while (*str)
		{
			if (match(pattern + 1, str))
				return (1);
			str++;
		}
		return (0);
	}
	else if (*pattern == '\0' || *str == '\0')
		return (*pattern == '\0' && *str == '\0');
	else if (*pattern == *str)
		return (match(pattern + 1, str + 1));
	return (0);
}

/*
* Goal: Get DIR data.
*
* Return: The DIR, NULL in case of malloc error.
*/
static DIR	*get_dir(void)
{
	char	*pwd;
	DIR		*dir;

	pwd = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!pwd)
	{
		ft_putendl_error("malloc error");
		return (NULL);
	}
	if (!getcwd(pwd, PATH_MAX))
	{
		ft_putendl_error("malloc error");
		free(pwd);
		return (NULL);
	}
	dir = opendir(pwd);
	free(pwd);
	if (!dir)
	{
		ft_putendl_error("opendir error");
		return (NULL);
	}
	return (dir);
}

/*
* Goal: Create a new mallco node and add it to lst.
*
* Return: 1, 0 if malloc error.
*
* Warning: lst and filename must not be null.
*/
static int	create_and_addback(t_list **lst, char *filename)
{
	t_list	*new;
	char	*filename_malloc;

	filename_malloc = ft_strdup(filename);
	if (!filename_malloc)
	{
		ft_putendl_error("malloc error");
		return (1);
	}
	new = ft_lstnew(filename_malloc);
	if (!new)
	{
		free(filename_malloc);
		ft_putendl_error("malloc error");
		return (1);
	}
	ft_lstadd_back(lst, new);
	return (0);
}

/*
* Goal: Find all the files in the current dirrectory.
*
* Return: 1 if it matchs, 0 if not.
*
* Warning: patern not be null.
*/
t_list	*find_matches(char *patern)
{
	DIR				*dir;
	struct dirent	*file;
	t_list			*matches;

	dir = get_dir();
	if (!dir)
		return (NULL);
	matches = NULL;
	file = readdir(dir);
	while (file != NULL)
	{
		if ((file->d_name[0] != '.' || patern[0] == '.')
			&& match(patern, file->d_name))
		{
			if (create_and_addback(&matches, file->d_name))
			{
				ft_lstclear(&matches, free);
				closedir(dir);
				return (NULL);
			}
		}
		file = readdir(dir);
	}
	closedir(dir);
	return (matches);
}
