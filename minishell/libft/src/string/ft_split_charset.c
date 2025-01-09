/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:07:52 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/09 17:15:16 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_in_charset(char *charset, char c) //keep this function please
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

static void	str_to_tab(char **tab, int size_tab, char *str, char *charset)
{
	int	count;
	int	count2;
	int	size;

	count = 0;
	while (count < size_tab)
	{
		size = 0;
		count2 = 0;
		while (*str && ft_is_in_charset(charset, *str))
			str++;
		while (str[size] && !ft_is_in_charset(charset, str[size]))
			size++;
		tab[count] = (char *)malloc(sizeof(char) * (size + 1));
		while (count2 < size)
		{
			tab[count][count2] = str[count2];
			count2++;
		}
		str += size + 1;
		tab[count][count2] = 0;
		count++;
	}
	tab[count] = 0;
}

char	**ft_split_charset(char *str, char *charset) //change with better one
{
	char	**tab;
	int		count;
	int		size_tab;

	count = 0;
	size_tab = 0;
	while (str[count] && ft_is_in_charset(charset, str[count]))
		count++;
	while (str[count])
	{
		size_tab++;
		count++;
		while (str[count] && !ft_is_in_charset(charset, str[count]))
			count++;
		while (str[count] && ft_is_in_charset(charset, str[count]))
			count++;
	}
	tab = (char **)malloc(sizeof(char *) * (size_tab + 1));
	if (!tab)
		return (0);
	str_to_tab(tab, size_tab, str, charset);
	return (tab);
}
