/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:20:57 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/24 11:07:39 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putnbr_fd(long n, int fd)
{
	return (ft_putnbr_base_fd(n, "0123456789", fd));
}

ssize_t	ft_putnbr_error(long n)
{
	return (ft_putnbr_fd(n, 2));
}

ssize_t	ft_putnbr(long n)
{
	return (ft_putnbr_fd(n, 1));
}
