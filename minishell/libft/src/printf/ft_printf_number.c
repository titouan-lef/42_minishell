/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:46:00 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/09 19:48:51 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static ssize_t	ft_printf_unbr_base(va_list arg, char *base, int fd)
{
	unsigned int	u;

	u = (unsigned int)va_arg(arg, unsigned int);
	return (ft_putunbr_base_fd(u, base, fd));
}

ssize_t	ft_printf_unbr(va_list arg, int fd)
{
	return (ft_printf_unbr_base(arg, "0123456789", fd));
}

ssize_t	ft_printf_unbr_lowhexa(va_list arg, int fd)
{
	return (ft_printf_unbr_base(arg, "0123456789abcdef", fd));
}

ssize_t	ft_printf_unbr_uphexa(va_list arg, int fd)
{
	return (ft_printf_unbr_base(arg, "0123456789ABCDEF", fd));
}

ssize_t	ft_printf_nbr(va_list arg, int fd)
{
	int	d;

	d = (int)va_arg(arg, int);
	return (ft_putnbr_fd(d, fd));
}
