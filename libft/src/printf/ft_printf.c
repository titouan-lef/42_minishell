/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:22:43 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/09 19:47:03 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static ssize_t	ft_conversion(char c, va_list arg, int fd)
{
	ssize_t	size;

	if (c == 'c')
		size = ft_printf_char(arg, fd);
	else if (c == 's')
		size = ft_printf_string(arg, fd);
	else if (c == 'p')
		size = ft_printf_address(arg, fd);
	else if (c == 'd' || c == 'i')
		size = ft_printf_nbr(arg, fd);
	else if (c == 'u')
		size = ft_printf_unbr(arg, fd);
	else if (c == 'x')
		size = ft_printf_unbr_lowhexa(arg, fd);
	else if (c == 'X')
		size = ft_printf_unbr_uphexa(arg, fd);
	else if (c == '%')
		size = ft_printf_percent(fd);
	else
		size = ft_printf_error(c, fd);
	return (size);
}

static ssize_t	ft_printf_result(const char *format, va_list arg, int fd)
{
	ssize_t	size;
	ssize_t	tmp_size;

	size = 0;
	while (*format)
	{
		if (*format != '%')
			tmp_size = ft_putchar_fd(*format, fd);
		else
		{
			++format;
			tmp_size = ft_conversion(*format, arg, fd);
		}
		if (tmp_size < 0)
			return (-1);
		size += tmp_size;
		++format;
	}
	return (size);
}

ssize_t	ft_printf(const char *format, ...)
{
	va_list	arg;
	ssize_t	size;

	if (!format)
		return (-1);
	va_start(arg, format);
	size = ft_printf_result(format, arg, 1);
	va_end(arg);
	return (size);
}

ssize_t	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	arg;
	ssize_t	size;

	if (!format)
		return (-1);
	va_start(arg, format);
	size = ft_printf_result(format, arg, fd);
	va_end(arg);
	return (size);
}
