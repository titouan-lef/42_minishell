/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:34:13 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/28 15:50:07 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toint(int c)
{
	return (c - '0');
}

int	ft_atoi(const char *nptr)
{
	int	symbol;
	int	nb;

	while (ft_isspace(*nptr))
		++nptr;
	symbol = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			symbol = -1;
		++nptr;
	}
	nb = 0;
	while (ft_isdigit(*nptr))
	{
		nb = nb * 10 + ft_toint(*nptr);
		++nptr;
	}
	return (nb * symbol);
}
