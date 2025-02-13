/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simplesort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:44:46 by tle-floc          #+#    #+#             */
/*   Updated: 2024/12/02 11:34:21 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_insertion_sort(int *tab, size_t n)
{
	size_t	i;
	size_t	j;
	int		tmp;

	i = 1;
	while (i < n)
	{
		tmp = tab[i];
		j = i;
		while (j > 0 && tab[j - 1] > tmp)
		{
			tab[j] = tab[j - 1];
			--j;
		}
		tab[j] = tmp;
		++i;
	}
}

void	ft_bubble_sort(int *tab, size_t n)
{
	size_t	i;

	while (n > 1)
	{
		--n;
		i = 0;
		while (i < n)
		{
			if (tab[i] > tab[i + 1])
				ft_swap(tab + i, tab + i + 1);
			++i;
		}
	}
}

void	ft_selection_sort(int *tab, size_t n)
{
	size_t	pos_max;
	size_t	i;

	while (n > 1)
	{
		--n;
		pos_max = 0;
		i = 1;
		while (i <= n)
		{
			if (tab[i] > tab[pos_max])
				pos_max = i;
			++i;
		}
		ft_swap(tab + pos_max, tab + n);
	}
}
