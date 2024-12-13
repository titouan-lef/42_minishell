/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:28:23 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/25 14:25:32 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

ssize_t	ft_printf_char(va_list arg)
{
	char	c;

	c = (char)va_arg(arg, int);
	return (ft_putchar(c));
}

ssize_t	ft_printf_percent(void)
{
	return (ft_putchar('%'));
}

ssize_t	ft_printf_string(va_list arg)
{
	char	*s;

	s = (char *)va_arg(arg, char *);
	if (!s)
		return (ft_putstr("(null)"));
	return (ft_putstr(s));
}

ssize_t	ft_printf_error(char c)
{
	ssize_t	len_percent;
	ssize_t	len_char;

	if (c == '\0')
		return (-1);
	len_percent = ft_putchar('%');
	if (len_percent < 0)
		return (-1);
	len_char = ft_putchar(c);
	if (len_char < 0)
		return (-1);
	return (len_percent + len_char);
}
