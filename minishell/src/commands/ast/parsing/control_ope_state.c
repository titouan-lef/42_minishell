/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_ope_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:59:28 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/22 12:06:28 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/*
* Goal: Create a sub tree until a closing parenthesis is found.
*
* Return: The sub tree (or NULL if error).
*/
static t_tree	*build_sub_tree(t_queue *queue, t_list **here_docs)
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
		sub_tree = next_state(sub_tree, queue, here_docs);
		if (tree_is_empty(sub_tree))
			return (NULL);
	}
	print_error_token_value("(");
	tree_clear(&sub_tree);
	return (NULL);
}

/*
* Goal: Manage the open parenthesis in tree.
*
* Return: The new tree (or NULL if error).
*
* Warning: Tree is a sub tree (junction operator or start of command),
* so a correct tree is empty.
*/
t_tree	*state_par_open(t_tree *sub_tree, t_queue *queue, t_list **here_docs)
{
	if (!tree_is_empty(sub_tree) || queue_is_empty(queue))
	{
		print_error_token(queue);
		tree_clear(&sub_tree);
		return (NULL);
	}
	remove_token(queue);
	sub_tree = build_sub_tree(queue, here_docs);
	return (sub_tree);
}

/*
* Goal: Add and manage junction operator (|, && and ||) in tree.
*
* Return: The new tree (or NULL if error).
*/
t_tree	*state_junction_ope(t_tree *tree, t_queue *queue, t_list **here_docs)
{
	t_token_name	type;
	t_tree			*sub_tree;

	tree = add_new_token(tree, queue);
	if (!tree)
		return (NULL);
	if (queue_is_empty(queue))
	{
		print_error_token_value(tree->token.value[0]);
		tree_clear(&tree);
		return (NULL);
	}
	type = queue_first_name(queue);
	sub_tree = common_state(NULL, queue, type, here_docs);
	if (tree_is_empty(sub_tree))
	{
		tree_clear(&tree);
		return (NULL);
	}
	tree_push_right(tree, sub_tree);
	return (tree);
}

/*
* Goal: Add and manage logical operator (&& and ||) in tree.
*
* Return: The new tree (or NULL if error).
*/
t_tree	*state_logical_ope(t_tree *tree, t_queue *queue, t_list **here_docs)
{
	if (tree_is_empty(tree))
	{
		print_error_token(queue);
		return (NULL);
	}
	tree = state_junction_ope(tree, queue, here_docs);
	return (tree);
}
