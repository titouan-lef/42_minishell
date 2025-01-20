/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:27:31 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/20 16:15:49 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Goal: Find size of a null terminated tab.
*
* Return: The size of the tab.
*/
int	size_tab(char **tab)
{
	int		size;

	size = 0;
	while (tab && tab[size])
		size++;
	return (size);
}

/*
* Goal: Join two null terminated tabs into one.
*
* Return: The joined tab.
*
* Warning: None.
*/
char	**tab_join(char **tab1, char **tab2)
{
	char	**new_tab;
	int		index;

	if (tab1 == NULL)
		return (tab2);
	if (tab2 == NULL)
		return (tab1);
	new_tab = (char **)ft_calloc(sizeof(char *),
			size_tab(tab1) + size_tab(tab2) + 1);
	if (!new_tab)
		return (NULL);
	index = 0;
	while (*tab1)
	{
		new_tab[index++] = *tab1;
		tab1++;
	}
	while (*tab2)
		new_tab[index++] = *(tab2++);
	return (new_tab);
}

/*
* Goal: Join two null terminated tabs into one and free the tabs.
*
* Return: The joined tab.
*/
char	**tab_join_and_free(char **tab1, char **tab2)
{
	char	**new_tab;

	new_tab = tab_join(tab1, tab2);
	if (new_tab != tab1)
		free(tab1);
	if (new_tab != tab2)
		free(tab2);
	return (new_tab);
}

/*
* Goal: Append str at the end of the tab.
*
* Return: The new tab, NULL is case of malloc error.
*/
char	**append_to_tab(char **tab, const char *str)
{
	int		j;
	char	**new_tab;

	new_tab = ft_calloc((size_tab(tab) + 2), sizeof(char *));
	if (!new_tab)
	{
		ft_clean_matrix((void **)tab);
		return (NULL);
	}
	j = 0;
	while (tab && tab[j])
	{
		new_tab[j] = tab[j];
		j++;
	}
	new_tab[j] = ft_strdup(str);
	if (!new_tab[j])
	{
		free(new_tab);
		ft_clean_matrix((void **)tab);
		return (NULL);
	}
	free(tab);
	return (new_tab);
}
