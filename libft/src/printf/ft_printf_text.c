/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:28:23 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/09 19:50:26 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

ssize_t	ft_printf_char(va_list arg, int fd)
{
	char	c;

	c = (char)va_arg(arg, int);
	return (ft_putchar_fd(c, fd));
}

ssize_t	ft_printf_percent(int fd)
{
	return (ft_putchar_fd('%', fd));
}

ssize_t	ft_printf_string(va_list arg, int fd)
{
	char	*s;

	s = (char *)va_arg(arg, char *);
	if (!s)
		return (ft_putstr_fd("(null)", fd));
	return (ft_putstr_fd(s, fd));
}

ssize_t	ft_printf_error(char c, int fd)
{
	ssize_t	len_percent;
	ssize_t	len_char;

	if (c == '\0')
		return (-1);
	len_percent = ft_putchar_fd('%', fd);
	if (len_percent < 0)
		return (-1);
	len_char = ft_putchar_fd(c, fd);
	if (len_char < 0)
		return (-1);
	return (len_percent + len_char);
}
