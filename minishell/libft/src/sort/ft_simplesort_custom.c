/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simplesort_custom.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:29:19 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/17 20:23:06 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Goal: Sort a 'tab' of 'nmemb' element, where every element has a size
* of 'size'. The function 'compar' allows to define is 2 elements are sorted
* (return less than 0), not sorted (return greater than 0) or equal (return 0).
*
* Warning: The 'size' of elements must be less than or equal to 100 and greater
* than 0.
*/
void	ft_insertion_qsort(void *tab, size_t nmemb, size_t size,
	int (*compar)(const void *, const void *))
{
	unsigned char	buff[100];
	size_t			i;
	size_t			j;

	if (size > 100)
	{
		ft_putendl_error("size in ft_insertion_qsort() to large");
		return ;
	}
	i = size;
	while (i / size < nmemb)
	{
		ft_memcpy(buff, tab + i, size);
		j = i;
		while (j > 0 && compar(tab + j - size, buff) > 0)
		{
			ft_memcpy(tab + j, tab + j - size, size);
			j -= size;
		}
		ft_memcpy(tab + j, buff, size);
		i += size;
	}
}
