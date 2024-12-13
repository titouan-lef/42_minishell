/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_change.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:00:16 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/26 19:00:16 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Goal: Apply f on any list element.
*
* Warning: 'f' mustn't be null.
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*
* Goal: Apply f on any list element and stock result on new list.
*
* Warning: 'f' mustn't be null.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	**last;
	t_list	*new;
	void	*new_content;

	result = NULL;
	last = &result;
	while (lst)
	{
		new_content = f(lst->content);
		new = ft_lstnew(new_content);
		if (!new)
		{
			if (del)
				del(new_content);
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_front(last, new);
		last = &new->next;
		lst = lst->next;
	}
	return (result);
}
