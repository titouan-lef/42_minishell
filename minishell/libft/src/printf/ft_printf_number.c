/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:46:00 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/30 11:00:38 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static ssize_t	ft_printf_unbr_base(va_list arg, char *base)
{
	unsigned int	u;

	u = (unsigned int)va_arg(arg, unsigned int);
	return (ft_putunbr_base(u, base));
}

ssize_t	ft_printf_unbr(va_list arg)
{
	return (ft_printf_unbr_base(arg, "0123456789"));
}

ssize_t	ft_printf_unbr_lowhexa(va_list arg)
{
	return (ft_printf_unbr_base(arg, "0123456789abcdef"));
}

ssize_t	ft_printf_unbr_uphexa(va_list arg)
{
	return (ft_printf_unbr_base(arg, "0123456789ABCDEF"));
}

ssize_t	ft_printf_nbr(va_list arg)
{
	int	d;

	d = (int)va_arg(arg, int);
	return (ft_putnbr(d));
}
