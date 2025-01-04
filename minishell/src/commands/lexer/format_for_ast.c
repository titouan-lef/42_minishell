/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_for_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:00:40 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/04 18:44:28 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Goal: Find size of a null terminated tab.
*
* Return: The size of the tab.
*
* Warning: None.
*/
static int	size_tab(char **tab)
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
static char	**tab_join(char **tab1, char **tab2)
{
	char	**new_tab;
	int		index;

	if (tab1 == NULL)
		return (tab2);
	if (tab2 == NULL)
		return (tab1);
	new_tab = (char **)ft_calloc(sizeof(char *),
			size_tab(tab1) + size_tab(tab2) + 1);
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
*
* Warning: None.
*/
static char	**tab_join_and_free(char **tab1, char **tab2)
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
* Goal: Push the tokens redir and cmd in the given token queue
*		if they are not empty.
*
* Return: None.
*
* Warning: token, redir and cmd must not be null.
*/
static void	push_redir_cmd(t_queue *tokens, t_token *redir, t_token *cmd)
{
	if (redir->value)
	{
		queue_push(tokens, *redir);
		redir->value = NULL;
	}
	if (cmd->value)
	{
		queue_push(tokens, *cmd);
		cmd->value = NULL;
	}
}

/*
* Goal: Groups the word and redir tokens.
*
* Return: The reorganized queue.
*
* Warning: token must not be null.
*/
t_queue	reorganize(t_queue tokens)
{
	t_queue	reorganized_tokens;
	t_token	token;
	t_token	cmd;
	t_token	redir;

	cmd.name = TOKEN_CMD;
	cmd.value = NULL;
	redir.name = TOKEN_REDIR;
	redir.value = NULL;
	reorganized_tokens = queue_create();
	while (tokens.head)
	{
		token = queue_pop(&tokens);
		if (token.name == TOKEN_WORD)
			cmd.value = tab_join_and_free(cmd.value, token.value);
		else if (token.name == TOKEN_REDIR)
			redir.value = tab_join_and_free(redir.value, token.value);
		else
		{
			push_redir_cmd(&reorganized_tokens, &redir, &cmd);
			queue_push(&reorganized_tokens, token);
		}
	}
	push_redir_cmd(&reorganized_tokens, &redir, &cmd);
	return (reorganized_tokens);
}
