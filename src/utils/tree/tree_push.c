/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:37:17 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/10 07:39:49 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
* Goal: Add 'sub_tree' on the left part of 'tree'.
*
* Warning: Tree mustn't be null and tree->left must be null.
*/
void	tree_push_left(t_tree *tree, t_tree *sub_tree)
{
	tree->left = sub_tree;
}

/*
* Goal: Add 'sub_tree' on the right part of 'tree'.
*
* Warning: Tree mustn't be null and tree->right must be null.
*/
void	tree_push_right(t_tree *tree, t_tree *sub_tree)
{
	tree->right = sub_tree;
}
