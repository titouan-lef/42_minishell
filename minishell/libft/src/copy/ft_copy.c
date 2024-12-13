/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:15:08 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/15 17:40:53 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Goal: Copy 'n' bytes from 'src' to 'dest'.
*
* Return: 'dest' pointer.
*
* Warning: 'n' and size of 'dest' are not verified.
* 'dest' and 'src' must not overlap.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	if (dest == NULL && src == NULL)
		return (dest);
	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		++i;
	}
	return (dest);
}

/*
* Goal: Copy 'n' bytes from 'src' to 'dest' even if they overlap.
*
* Return: 'dest' pointer.
*
* Warning: 'n' and size of 'dest' are not verified.
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	if (dest <= src || src + n < dest)
	{
		ft_memcpy(dest, src, n);
		return (dest);
	}
	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	while (n > 0)
	{
		--n;
		d[n] = s[n];
	}
	return (dest);
}

void	*ft_memdup(const void *src, size_t n)
{
	void	*dest;

	dest = (void *)malloc(n);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, src, n);
	return (dest);
}
