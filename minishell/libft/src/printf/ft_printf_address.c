/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:09:05 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/25 14:25:57 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

ssize_t	ft_printf_address(va_list arg)
{
	unsigned long	addr;
	ssize_t			len_prefix;
	ssize_t			len_addr;

	addr = (unsigned long)va_arg(arg, unsigned long);
	if (addr == 0)
		return (ft_putstr("(nil)"));
	len_prefix = ft_putstr("0x");
	if (len_prefix < 0)
		return (-1);
	len_addr = ft_putunbr_base(addr, "0123456789abcdef");
	if (len_addr < 0)
		return (-1);
	return (len_prefix + len_addr);
}
