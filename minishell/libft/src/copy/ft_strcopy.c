/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:20:03 by tle-floc          #+#    #+#             */
/*   Updated: 2024/12/15 20:00:12 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Goal: Copy the first 'size'-1 characters of 'src' to 'dst' and finish with \0.
* If the 'src' size is less than 'size'-1, copy 'src' to 'dst'.
*
* Return: 'src' size.
*
* Warning: 'dst' size is not verified.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	--size;
	if (src_len < size)
		size = src_len;
	ft_memcpy(dst, src, size);
	dst[size] = '\0';
	return (src_len);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dst;
	size_t	len;

	len = ft_strnlen(s, n);
	dst = (char *)malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s, len);
	dst[len] = '\0';
	return (dst);
}

char	*ft_strdup(const char *s)
{
	size_t	size;
	size_t	len;
	char	*result;

	len = ft_strlen(s);
	size = (len + 1) * sizeof(char);
	result = ft_memdup(s, size);
	return (result);
}
