/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_ope_state_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:59:28 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/13 15:10:45 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
* Goal: Create a sub tree until a closing parenthesis is found.
*
* Return: The sub tree, NULL if error.
*/
static t_tree	*build_sub_tree(t_queue *queue, t_data *data)
{
	t_tree			*sub_tree;
	t_token_name	type;

	sub_tree = NULL;
	while (!queue_is_empty(queue))
	{
		type = queue_first_name(queue);
		if (type == TOKEN_PAR_CLOSE)
		{
			if (tree_is_empty(sub_tree))
				print_error_token(queue);
			else
				remove_token(queue);
			return (sub_tree);
		}
		sub_tree = next_state(sub_tree, queue, data);
		if (tree_is_empty(sub_tree))
			return (NULL);
	}
	print_error_token_value("(");
	tree_clear(&sub_tree);
	return (NULL);
}

/*
* Goal: Create a sub tree and add it on the right of the junction operator node.
*
* Return: The new tree, NULL if error.
*/
static t_tree	*build_sub_tree_right(t_tree *tree, t_queue *queue,
					t_data *data)
{
	t_token_name	type;
	t_tree			*sub_tree;

	type = queue_first_name(queue);
	sub_tree = common_state(NULL, queue, type, data);
	if (tree_is_empty(sub_tree))
	{
		tree_clear(&tree);
		return (NULL);
	}
	tree_push_right(tree, sub_tree);
	return (tree);
}

/*
* Goal: Manage the open parenthesis in tree.
*
* Return: The new tree, NULL if error.
*
* Warning: Tree is a sub tree (junction operator or start of command),
*		so a correct tree is empty.
*/
t_tree	*state_par_open(t_tree *sub_tree, t_queue *queue, t_data *data)
{
	t_token_name	type;

	if (!tree_is_empty(sub_tree) || queue_is_empty(queue))
	{
		print_error_token(queue);
		tree_clear(&sub_tree);
		return (NULL);
	}
	remove_token(queue);
	sub_tree = build_sub_tree(queue, data);
	if (!sub_tree || queue_is_empty(queue))
		return (sub_tree);
	type = queue_first_name(queue);
	if (type == TOKEN_CMD)
	{
		print_error_token(queue);
		tree_clear(&sub_tree);
		return (NULL);
	}
	if (type == TOKEN_PIPE)
		sub_tree = state_junction_ope(sub_tree, queue, data);
	return (sub_tree);
}

/*
* Goal: Add and manage junction operator (|, && and ||) in tree.
*
* Return: The new tree, NULL if error.
*/
t_tree	*state_junction_ope(t_tree *tree, t_queue *queue, t_data *data)
{
	if (tree_is_empty(tree))
	{
		print_error_token(queue);
		return (NULL);
	}
	tree = add_new_token(tree, queue);
	if (tree_is_empty(tree))
		return (NULL);
	if (queue_is_empty(queue))
	{
		print_error_token_value(tree->token.value[0]);
		tree_clear(&tree);
		return (NULL);
	}
	tree = build_sub_tree_right(tree, queue, data);
	return (tree);
}
