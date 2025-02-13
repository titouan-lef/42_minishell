/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:20:03 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/04 13:08:02 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Goal: Copy every characters from 'src' to 'dest'.
*
* Return: 'dest' pointer.
*
* Warning: size of 'dest' are not verified.
* 'dest' and 'src' must not overlap.
* 'dest' and 'src' must not be null.
*/
char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}

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
