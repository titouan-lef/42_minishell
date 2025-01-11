/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:07:52 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/10 12:02:13 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_in_charset(char const *charset, char c)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

static size_t	ft_count_substr(char const *s, char const *charset)
{
	size_t	count;
	int		is_new_substr;

	count = 0;
	is_new_substr = 1;
	while (*s != '\0')
	{
		if (ft_is_in_charset(charset, *s))
			is_new_substr = 1;
		else if (is_new_substr)
		{
			is_new_substr = 0;
			++count;
		}
		++s;
	}
	return (count);
}

static char	**ft_fill_result(char const *s, char const *charset, char **result)
{
	size_t		i;
	const char	*end;

	i = 0;
	while (*s != '\0')
	{
		while (ft_is_in_charset(charset, *s))
			++s;
		if (*s == '\0')
			break ;
		end = s + 1 + ft_strcspn(s + 1, charset);
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

/*
* Goal: Do a ft_split with 'charset' (char *) and not a char.
*
* Return: An array null terminated (or null if error).
*
* Warning: 'charset' mustn't be null.
*/
char	**ft_split_charset(char const *s, char const *charset)
{
	char	**result;
	size_t	nb_substr;

	if (!s)
		return (NULL);
	nb_substr = ft_count_substr(s, charset);
	result = (char **)malloc((nb_substr + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result = ft_fill_result(s, charset, result);
	return (result);
}
