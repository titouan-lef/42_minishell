/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:14:43 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/22 10:16:50 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return (-1);
	len = ft_strlen(s);
	return (write(fd, s, len));
}

ssize_t	ft_putstr_error(char *s)
{
	return (ft_putstr_fd(s, 2));
}

ssize_t	ft_putstr(char *s)
{
	return (ft_putstr_fd(s, 1));
}
