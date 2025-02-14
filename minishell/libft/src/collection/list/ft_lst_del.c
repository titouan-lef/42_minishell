/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:00:25 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/28 15:50:47 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstdel(t_list *lst, void (*del)(void *))
{
	if (del)
		del(lst->content);
	free(lst);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
		ft_lstdel(lst, del);
}

/*
* Goal: Remove the first element.
*
* Return: The next element.
*
* Warning: 'lst' mustn't be null.
*/
t_list	*ft_lstremove_front(t_list *lst, void (*del)(void *))
{
	t_list	*next;

	next = lst->next;
	ft_lstdel(lst, del);
	return (next);
}

/*
* Goal: Clear the list and set lists pointer to null.
*
* Warning: 'lst' is the list's address, so it mustn't be null.
*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	while (*lst)
		*lst = ft_lstremove_front(*lst, del);
}
