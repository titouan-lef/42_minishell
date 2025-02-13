/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:35:48 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/26 16:35:48 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	number_digits(int n)
{
	size_t	size;

	n = n / 10;
	size = 1;
	while (n != 0)
	{
		n = n / 10;
		++size;
	}
	return (size);
}

static void	write_numbers(unsigned int nbp, char *str, size_t size)
{
	--size;
	str[size] = '\0';
	while (size > 0)
	{
		--size;
		str[size] = ft_tochar(nbp % 10);
		nbp = nbp / 10;
	}
}

char	*ft_itoa(int n)
{
	char			*result;
	unsigned int	nbp;
	size_t			size;
	size_t			offset;

	nbp = n;
	offset = 0;
	if (n < 0)
	{
		nbp = -n;
		++offset;
	}
	size = number_digits(n) + offset + 1;
	result = (char *)malloc(size * sizeof(char));
	if (!result)
		return (NULL);
	write_numbers(nbp, result + offset, size - offset);
	if (offset)
		result[0] = '-';
	return (result);
}
