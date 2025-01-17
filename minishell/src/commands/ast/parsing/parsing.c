/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:49:43 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/17 16:59:49 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "commands.h"

/*
* Goal: Check if a there is an syntax error with parenthesis.
*
* Return: 0 if error, 1 if not.
*
* Warning: nb_par must not be null.
*/
int	valid_parenthesis(char *input)
{
	int		nb_par;

	nb_par = 0;
	while (*input)
	{
		if (*input == '(')
			nb_par++;
		if (*input == ')')
			nb_par--;
		if (nb_par < 0)
		{
			printf("syntax error near token '%c'\n", *input);
			return (0);
		}
		input++;
	}
	if (nb_par > 0)
	{
		printf("syntax error\n"); //heredoc ?
		return (0);
	}
	return (1);
}

t_tree	*next_state(t_tree *tree, t_queue *queue, t_list **here_docs)
{
	t_token_name	type;

	type = queue_first_name(queue);
	if (type == TOKEN_OPE)
		tree = state_ope(tree, queue, here_docs);
	else
		tree = common_state(tree, queue, type, here_docs);
	return (tree);
}

t_data	get_tree_data(t_queue *queue)
{
	t_tree	*tree;
	t_list	*here_docs;
	t_data	data;

	tree = NULL;
	here_docs = NULL;
	while (!queue_is_empty(queue))
	{
		tree = next_state(tree, queue, &here_docs);
		if (tree == NULL)
			break ;
	}
	queue_clear(queue);
	data.tree = tree;
	data.lst = here_docs;
	return (data);
}
