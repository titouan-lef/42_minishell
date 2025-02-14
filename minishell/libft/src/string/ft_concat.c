/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:10:20 by tle-floc          #+#    #+#             */
/*   Updated: 2024/12/10 17:41:33 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Goal: Add characters of 'src' at the end of 'dst' to get a string of maximum
* size 'size'-1. If 'size' isn't greater than 'dst' size, 'dst' don't change.
*
* Return: Maximal 'dst' size if working and 'src' size plus 'size' else.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_size;
	size_t	len;

	dst_size = 0;
	if (dst)
		dst_size = ft_strlen(dst);
	if (size <= dst_size)
	{
		len = ft_strlen(src);
		return (len + size);
	}
	len = ft_strlcpy(dst + dst_size, src, size - dst_size);
	return (dst_size + len);
}

/*
* Goal: Create a new string result of concatenation of 'n1' characters of 's1'
* and 'n2' characters of 's2'.
*
* Return: New string which can be free.
*
* Warning: parameters are not verified.
*/
char	*ft_strnjoin(const char *s1, size_t n1, const char *s2, size_t n2)
{
	char	*str;

	str = (char *)malloc((n1 + n2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, n1);
	ft_memcpy(str + n1, s2, n2);
	str[n1 + n2] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	n1;
	size_t	n2;

	if (!s1 || !s2)
		return (NULL);
	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	return (ft_strnjoin(s1, n1, s2, n2));
}
