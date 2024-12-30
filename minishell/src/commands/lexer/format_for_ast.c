/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_for_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:00:40 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/30 02:55:37 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_tab(char **tab)
{
	int		size;

	size = 0;
	while (tab[size])
		size++;
	return (size);
}

char	**tab_join(char **tab1, char **tab2)
{
	char	**new_tab;
	int		index;

	if (tab1 ==  NULL && tab2 == NULL)
		return (NULL);
	else if (tab1 ==  NULL)
		return (tab2);
	else if (tab2 ==  NULL)
		return (tab1);
	new_tab = (char **)ft_calloc(sizeof(char *), size_tab(tab1) + size_tab(tab2) + 1);
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

t_element	*reorganize(t_queue tokens)
{
	t_queue	reorganized_tokens;
	t_token	token;
	t_token	cmd;
	t_token	redir;
	char	**new_tab;

	cmd.name = TOKEN_CMD;
	cmd.value = NULL;
	redir.name = TOKEN_REDIR;
	redir.value = NULL;
	reorganized_tokens = queue_create();
	while (tokens.head)
	{
		token = queue_pop(&tokens);
		if (token.name == TOKEN_WORD)
		{
			new_tab = tab_join(cmd.value, token.value);
			free(cmd.value);
			cmd.value = new_tab;
		}
		else if (token.name == TOKEN_REDIR)
		{
			new_tab = tab_join(redir.value, token.value);
			free(redir.value);
			redir.value = new_tab;
		}
		else
		{
			if (redir.value)
			{
				queue_push(&reorganized_tokens, redir);
				redir.value = NULL;
			}
			if (cmd.value)
			{
				queue_push(&reorganized_tokens, cmd);
				cmd.value = NULL;
			}
			queue_push(&reorganized_tokens, token);
		}
	}
	if (redir.value)
	{
		queue_push(&reorganized_tokens, redir);
		redir.value = NULL;
	}
	if (cmd.value)
	{
		queue_push(&reorganized_tokens, cmd);
		cmd.value = NULL;
	}
	return (reorganized_tokens.head);
}
