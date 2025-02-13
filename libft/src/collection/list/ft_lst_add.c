/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:59:59 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/26 18:59:59 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Goal: Add an element at the end of the list.
*
* Warning: 'lst' is the list's address, so it mustn't be null.
*/
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return ;
	tmp = ft_lstlast(*lst);
	if (!tmp)
		*lst = new;
	else
		tmp->next = new;
}

/*
* Goal: Add an element at the begining of the list.
*
* Warning: 'lst' is the list's address, so it mustn't be null.
*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*last_new;

	if (!new)
		return ;
	last_new = ft_lstlast(new);
	last_new->next = *lst;
	*lst = new;
}
