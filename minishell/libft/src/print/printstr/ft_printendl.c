/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printendl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:17:46 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/22 10:20:15 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putendl_fd(char *s, int fd)
{
	ssize_t	result1;
	ssize_t	result2;

	result1 = ft_putstr_fd(s, fd);
	if (result1 < 0)
		return (result1);
	result2 = ft_putchar_fd('\n', fd);
	if (result2 < 0)
		return (result2);
	return (result1 + result2);
}

ssize_t	ft_putendl_error(char *s)
{
	return (ft_putendl_fd(s, 2));
}

ssize_t	ft_putendl(char *s)
{
	return (ft_putendl_fd(s, 1));
}
