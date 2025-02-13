/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsignednumber_base.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:30:49 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/24 11:06:03 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putunbr_base_fd(unsigned long n, char *base, int fd)
{
	ssize_t			result;
	ssize_t			result_tmp;
	size_t			baselen;
	unsigned long	divisor;

	baselen = ft_strlen(base);
	if (baselen == 0)
		return (-1);
	result = 0;
	divisor = 1;
	while (n / divisor >= baselen)
		divisor *= baselen;
	while (divisor > 1)
	{
		result_tmp = ft_putchar_fd(base[n / divisor], fd);
		if (result_tmp < 0)
			return (result_tmp);
		result += result_tmp;
		n = n % divisor;
		divisor = divisor / baselen;
	}
	result_tmp = ft_putchar_fd(base[n], fd);
	if (result_tmp < 0)
		return (result_tmp);
	return (result + result_tmp);
}

ssize_t	ft_putunbr_base_error(unsigned long n, char *base)
{
	return (ft_putunbr_base_fd(n, base, 2));
}

ssize_t	ft_putunbr_base(unsigned long n, char *base)
{
	return (ft_putunbr_base_fd(n, base, 1));
}
