/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:07:52 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/10 11:07:37 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_substr(char const *s, int c)
{
	const unsigned char	*p;
	unsigned char		uc;
	size_t				count;
	int					is_new_substr;

	p = (const unsigned char *)s;
	uc = (unsigned char)c;
	count = 0;
	is_new_substr = 1;
	while (*p != '\0')
	{
		if (*p == uc)
			is_new_substr = 1;
		else if (is_new_substr)
		{
			is_new_substr = 0;
			++count;
		}
		++p;
	}
	return (count);
}

static char	**ft_fill_result(char const *s, char c, char **result)
{
	size_t	i;
	char	*end;

	i = 0;
	while (*s != '\0')
	{
		while (*s == c)
			++s;
		if (*s == '\0')
			break ;
		end = ft_strchrnul(s + 1, c);
		result[i] = ft_substr(s, 0, end - s);
		if (!result[i])
		{
			ft_free_matrix((void **)result, i);
			return (NULL);
		}
		++i;
		s = end;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	nb_substr;

	if (!s)
		return (NULL);
	nb_substr = ft_count_substr(s, c);
	result = (char **)malloc((nb_substr + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result = ft_fill_result(s, c, result);
	return (result);
}
