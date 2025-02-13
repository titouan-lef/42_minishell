/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_substr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:18:35 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/15 17:45:09 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	while (*set != '\0')
	{
		if (c == *set)
			return (1);
		++set;
	}
	return (0);
}

static size_t	strlen_trim(const char *s, char const *set)
{
	size_t	size;
	size_t	i;

	size = 1;
	i = 1;
	while (s[i] != '\0')
	{
		if (!is_in_set(s[i], set))
			size = i + 1;
		++i;
	}
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;

	if (!s)
		return (NULL);
	while (start > 0)
	{
		if (*s == '\0')
		{
			result = (char *)ft_calloc(1, sizeof(char));
			return (result);
		}
		--start;
		++s;
	}
	result = ft_strndup(s, len);
	return (result);
}

/*
* Goal: Create a copy of 's1' without the characters specified in 'set'
* from the beginning and the end.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	char	*substr;

	if (!s1 || !set)
		return (NULL);
	while (*s1 != '\0' && is_in_set(*s1, set))
		++s1;
	if (*s1 == '\0')
	{
		substr = (char *)ft_calloc(1, sizeof(char));
		return (substr);
	}
	size = strlen_trim(s1, set);
	substr = (char *)malloc((size + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s1, size);
	substr[size] = '\0';
	return (substr);
}
