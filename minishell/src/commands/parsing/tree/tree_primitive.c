/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_primitive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:44:48 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/04 15:08:12 by tle-floc         ###   ########.fr       */
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
void    tree_add_parent(t_tree **tree, t_token token)
{
	t_tree	parent;

    parent = tree_create(token);
    parent.left = *tree;
    *tree = &parent;
}

void	tree_clear(t_tree *tree)
{
	if (tree_is_empty(tree))
        return ;
    // clear token
    tree_clear(tree->left);
    tree_clear(tree->right);
    free(tree);
    tree = NULL;
}

t_tree	tree_create(t_token token)
{
	t_tree	tree;

    tree.token = token;
	tree.left = NULL;
	tree.right = NULL;
	return (tree);
}