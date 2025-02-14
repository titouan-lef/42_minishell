/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:09:05 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/09 19:45:26 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

ssize_t	ft_printf_address(va_list arg, int fd)
{
	unsigned long	addr;
	ssize_t			len_prefix;
	ssize_t			len_addr;

	addr = (unsigned long)va_arg(arg, unsigned long);
	if (addr == 0)
		return (ft_putstr_fd("(nil)", fd));
	len_prefix = ft_putstr_fd("0x", fd);
	if (len_prefix < 0)
		return (-1);
	len_addr = ft_putunbr_base_fd(addr, "0123456789abcdef", fd);
	if (len_addr < 0)
		return (-1);
	return (len_prefix + len_addr);
}
