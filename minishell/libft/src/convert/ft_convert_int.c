/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:34:13 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/10 13:08:02 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Goal: Add digit 'c' at the end of 'nb'.
* nb > INT_MAX / 10 allows to test :
* 	nb * 10 > INT_MAX.
* digit > INT_MAX - nb allows to test :
* 	nb + digit > INT_MAX.
*
* Return: The new number after add the digit 'c' or -1 if error.
*
* Warning: Overflow is an error.
*/
static int	ft_update_number(int nb, char c)
{
	int	digit;

	if (nb > INT_MAX / 10)
		return (-1);
	nb *= 10;
	digit = ft_toint(c);
	if (digit > INT_MAX - nb)
		return (-1);
	return (nb + digit);
}

/*
* Goal: Convert 'nptr' to a int.
*
* Return: A positive int or -1 if error.
*
* Warning: Overflow and no digit are errors.
*/
int	ft_to_positive_int(const char *nptr)
{
	int	nb;

	if (*nptr == '\0')
		return (-1);
	nb = 0;
	while (*nptr && nb >= 0)
	{
		if (!ft_isdigit(*nptr))
			return (-1);
		nb = ft_update_number(nb, *nptr);
		++nptr;
	}
	return (nb);
}

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
