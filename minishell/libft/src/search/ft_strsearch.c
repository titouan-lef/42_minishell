/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:18:06 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/10 11:27:04 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && !ft_is_in_charset(reject, s[i]))
		++i;
	return (i);
}

char	*ft_strchrnul(const char *s, int c)
{
	const unsigned char	*p;
	unsigned char		uc;

	p = (const unsigned char *) s;
	uc = (const unsigned char) c;
	while (*p != '\0' && *p != uc)
		++p;
	return ((char *)p);
}

char	*ft_strchr(const char *s, int c)
{
	const unsigned char	*p;
	unsigned char		uc;

	uc = (unsigned char)c;
	if (uc == '\0')
	{
		s += ft_strlen(s);
		return ((char *)s);
	}
	p = (const unsigned char *)s;
	while (*p != '\0')
	{
		if (*p == uc)
			return ((char *)p);
		++p;
	}
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	const unsigned char	*p;
	const unsigned char	*last;
	unsigned char		uc;

	uc = (unsigned char)c;
	if (uc == '\0')
	{
		s += ft_strlen(s);
		return ((char *)s);
	}
	p = (const unsigned char *)s;
	last = NULL;
	while (*p != '\0')
	{
		if (*p == uc)
			last = p;
		++p;
	}
	return ((char *)last);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	len_big;
	size_t	len_little;

	if (*little == '\0')
		return ((char *)big);
	if (!big && len == 0)
		return (NULL);
	len_big = ft_strlen(big);
	if (len_big < len)
		len = len_big;
	len_little = ft_strlen(little);
	i = 0;
	while (i + len_little <= len)
	{
		if (ft_strncmp(big + i, little, len_little) == 0)
			return ((char *)big + i);
		++i;
	}
	return (NULL);
}
