/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:22:43 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/30 10:59:38 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static ssize_t	ft_conversion(char c, va_list arg)
{
	ssize_t	size;

	if (c == 'c')
		size = ft_printf_char(arg);
	else if (c == 's')
		size = ft_printf_string(arg);
	else if (c == 'p')
		size = ft_printf_address(arg);
	else if (c == 'd' || c == 'i')
		size = ft_printf_nbr(arg);
	else if (c == 'u')
		size = ft_printf_unbr(arg);
	else if (c == 'x')
		size = ft_printf_unbr_lowhexa(arg);
	else if (c == 'X')
		size = ft_printf_unbr_uphexa(arg);
	else if (c == '%')
		size = ft_printf_percent();
	else
		size = ft_printf_error(c);
	return (size);
}

static ssize_t	ft_printf_result(const char *format, va_list arg)
{
	ssize_t	size;
	ssize_t	tmp_size;

	size = 0;
	while (*format)
	{
		if (*format != '%')
			tmp_size = ft_putchar(*format);
		else
		{
			++format;
			tmp_size = ft_conversion(*format, arg);
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
	size = ft_printf_result(format, arg);
	va_end(arg);
	return (size);
}
