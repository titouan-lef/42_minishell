/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 00:20:34 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/23 20:38:39 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static void	fill_str(char *random_string, int fd, size_t length)
{
	char	random_char;
	size_t	i;

	i = 0;
	while (i < length)
	{
		if (read(fd, &random_char, 1) != 1)
		{
			ft_printf_fd(2, "%s: %s\n", NAME, ERR_RND);
			free(random_string);
			random_string = NULL;
			break ;
		}
		if (ft_isalnum(random_char))
			random_string[i++] = random_char;
	}
}

/*
* Goal: Generate a random string of alpha numeric characters.
*
* Return: The generated string.
*/
char	*generate_random_string(size_t length)
{
	int		fd;
	char	*random_string;

	random_string = (char *)ft_calloc((length + 1), sizeof(char));
	if (!random_string)
		return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_RND);
		free(random_string);
		return (NULL);
	}
	fill_str(random_string, fd, length);
	close(fd);
	return (random_string);
}
