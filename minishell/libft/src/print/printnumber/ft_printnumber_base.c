/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnumber_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:26:42 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/24 11:07:14 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putnbr_base_fd(long n, char *base, int fd)
{
	ssize_t	result1;
	ssize_t	result2;

	if (n >= 0)
		return (ft_putunbr_base_fd(n, base, fd));
	result1 = ft_putchar_fd('-', fd);
	if (result1 < 0)
		return (result1);
	result2 = ft_putunbr_base_fd(-n, base, fd);
	if (result2 < 0)
		return (result2);
	return (result1 + result2);
}

ssize_t	ft_putnbr_base_error(long n, char *base)
{
	return (ft_putnbr_base_fd(n, base, 2));
}

ssize_t	ft_putnbr_base(long n, char *base)
{
	return (ft_putnbr_base_fd(n, base, 1));
}
