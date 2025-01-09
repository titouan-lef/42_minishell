/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:49:43 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/09 19:19:13 by tle-floc         ###   ########.fr       */
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

t_tree	*next_state(t_tree *tree, t_queue *queue)
{
	t_token_name	type;

	type = queue_first_name(queue);
	if (type == TOKEN_OPE)
		tree = state_ope(tree, queue);
	else
		tree = common_state(tree, queue, type);
	return (tree);
}

t_tree	*get_tree(t_queue *queue)
{
	t_tree	*tree;

	tree = NULL;
	while (!queue_is_empty(queue))
	{
		tree = next_state(tree, queue);
		if (tree == NULL)
			break ;
	}
	queue_clear(queue);
	tree_clear(&tree);//todo remove
	tree = NULL;//todo remove
	/*--//
	breadth_first_search(tree);
	ft_printf("\n\n");
	tree_traversal_in_order(tree);
	//--*/
	return (tree);
}
