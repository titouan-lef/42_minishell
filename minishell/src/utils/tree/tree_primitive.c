/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_primitive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:44:48 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/10 15:46:11 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
* Goal: Check if tree is empty.
*
* Return: 1 if tree is empyt, 0 if not
*/
int	tree_is_empty(t_tree *tree)
{
	return (tree == NULL);
}

/*
* Goal: Add a new node at the top that contains 'token'.
*
* Warning: The old tree will be on the new node left.
*		Funtion returns NULL if malloc fails.
*/
t_tree	*tree_add_parent(t_tree *tree, t_token token)
{
	t_tree	*parent;

	parent = tree_create(token);
	if (tree_is_empty(parent))
		return (NULL);
	tree_push_left(parent, tree);
	return (parent);
}

/*
* Goal: Clear the tree.
*/
void	tree_clear(t_tree **tree)
{
	if (tree_is_empty(*tree))
		return ;
	token_clear((*tree)->token);
	tree_clear(&(*tree)->left);
	tree_clear(&(*tree)->right);
	tree_push_left(*tree, NULL);
	tree_push_right(*tree, NULL);
	free(*tree);
	*tree = NULL;
}

/*
* Goal: Create a tree node with value of 'token'.
*
* Return: The node, NULL if malloc fails.
*/
t_tree	*tree_create(t_token token)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->token = token;
	tree_push_left(tree, NULL);
	tree_push_right(tree, NULL);
	return (tree);
}
