/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:34:13 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/10 17:02:52 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Goal: Add digit 'c' at the end of 'nb'.
* 'is_neg' is equal to 0 or 1.
* nb > max / 10 allows to test :
* 	nb * 10 > max.
* digit - is_neg > max - nb allows to test :
* 	nb + digit > max + is_neg.
*
* Return: The new number after add the digit 'c' or 1 if error.
*
* Warning: Overflow is an error.
*/
static int	ft_update_number(long long *nb, char c, int is_neg, long long max)
{
	long long	digit;

	if (*nb > max / 10)
		return (1);
	*nb *= 10;
	digit = ft_toint(c);
	if (digit - is_neg > max - *nb)
		return (1);
	*nb += digit;
	return (0);
}

/*
* Goal: Add digit 'c' at the end of 'nb'.
*
* Return: 0 on success, 2 if not number and 3 if overflow.
*/
static int	ft_char_to_number(long long *nb, const char *nptr, int is_neg,
				long long max)
{
	while (*nptr)
	{
		if (!ft_isdigit(*nptr))
			return (2);
		if (ft_update_number(nb, *nptr, is_neg, max))
			return (3);
		++nptr;
	}
	return (0);
}

/*
* Goal: Convert 'nptr' to a long long.
*
* Return: A long long and set status to :
* 	0 on success.
* 	1 if not a number.
* 	2 if there is a non-digit character.
* 	3 if overflow.
*/
long long	ft_to_number(const char *nptr, int *status, long long max)
{
	int			is_neg;
	long long	nb;

	is_neg = 0;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			is_neg = 1;
		++nptr;
	}
	nb = 0;
	if (*nptr == '\0')
	{
		*status = 1;
		return (nb);
	}
	*status = ft_char_to_number(&nb, nptr, is_neg, max);
	if (is_neg)
		nb = -nb;
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
