/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:29:53 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/05 16:27:51 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	compare_lexicographicly(char char1, char char2)
{
	int	is_char1_num;
	int	is_char2_num;
	int	is_char1_alnum;
	int	is_char2_alnum;

	is_char1_num = ft_isdigit(char1);
	is_char2_num = ft_isdigit(char2);
	is_char1_alnum = ft_isalnum(char1);
	is_char2_alnum = ft_isalnum(char2);
	if (!is_char1_num && is_char2_num)
		return (1);
	if (is_char1_num && !is_char2_num)
		return (-1);
	if (!is_char1_alnum && is_char2_alnum)
		return (-1);
	if (is_char1_alnum && !is_char2_alnum)
		return (1);
	if (ft_isupper(char1) && ft_islower(char2))
		return (char1 - char2 + 32);
	if (ft_islower(char1) && ft_isupper(char2))
		return (char1 - char2 - 32);
	return (char1 - char2);
}

int	strcmp_lexicographicly(const void *p1, const void *p2)
{
	size_t	i;
	char	*str1;
	char	*str2;
	int		result;

	i = 0;
	str1 = *(char **)p1;
	str2 = *(char **)p2;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		result = compare_lexicographicly(str1[i], str2[i]);
		if (result != 0)
			return (result);
		i++;
	}
	result = ft_strcmp(str1, str2);
	return (-result);
}

int	ft_void_strcmp(const void *s1, const void *s2)
{
	char	*str1;
	char	*str2;
	int		result;

	str1 = *(char **)s1;
	str2 = *(char **)s2;
	result = ft_strcmp(str1, str2);
	return (result);
}
