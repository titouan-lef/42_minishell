/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsignednumber.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:33:53 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/24 11:06:28 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putunbr_fd(unsigned long n, int fd)
{
	return (ft_putunbr_base_fd(n, "0123456789", fd));
}

ssize_t	ft_putunbr_error(unsigned long n)
{
	return (ft_putunbr_fd(n, 2));
}

ssize_t	ft_putunbr(unsigned long n)
{
	return (ft_putunbr_fd(n, 1));
}
