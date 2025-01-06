/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_primitive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:44:48 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/06 14:20:22 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

int	tree_is_empty(t_tree *tree)
{
	return (tree == NULL);
}

/*
* Goal: Add a new node at the top that contains 'token'.
*
* Warning: The old tree will be on the new node left.
*/
t_tree	*tree_add_parent(t_tree *tree, t_token token)
{
	t_tree	*parent;

	parent = tree_create(token);
	if (!parent)
		return (NULL);
	parent->left = tree;
	tree = parent;
	return (tree);
}

void	tree_clear(t_tree **tree)
{
	t_tree	*sub_tree_left;
	t_tree	*sub_tree_right;

	if (tree_is_empty(*tree))
		return ;
	sub_tree_left = (*tree)->left;
	sub_tree_right = (*tree)->right;
	// clear token
	tree_clear(&sub_tree_left);
	tree_clear(&sub_tree_right);
	sub_tree_left = NULL;
	sub_tree_right = NULL;
	free(*tree);
	*tree = NULL;
}

t_tree	*tree_create(t_token token)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->token = token;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}
