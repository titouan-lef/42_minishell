/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 00:20:34 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/17 21:06:56 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/*
* Goal: Generate a random string of alpha numeric characters.
*
* Return: The generated string.
*/
char	*generate_random_string(size_t length)
{
	int		fd;
	char	random_char;
	char	*random_string;
	size_t	i;

	random_string = (char *)ft_calloc((length + 1), sizeof(char));
	if (!random_string)
		return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_error("Impossible to geneate a here_doc name");
		free(random_string);
		return (NULL);
	}
	i = 0;
	while (i < length)
	{
		if (read(fd, &random_char, 1) != 1) //protection + free random_string
			return (NULL);
		if (ft_isalnum(random_char))
			random_string[i++] = random_char;
	}
	close(fd);
	return (random_string);
}
