/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:37:17 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/07 14:26:05 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

/*
* Goal: Add 'sub_tree' on the left part of 'tree'
*
* Return: 0 if error, 1 else
*/
int	tree_push_left(t_tree *tree, t_tree *sub_tree)
{
	if (tree_is_empty(tree) || tree->left != NULL)
	{
		ft_putendl_error("Error tree push left");
		return (0);
	}
	tree->left = sub_tree;
	return (1);
}

/*
* Goal: Add 'sub_tree' on the right part of 'tree'
*
* Return: 0 if error, 1 else
*/
int	tree_push_right(t_tree *tree, t_tree *sub_tree)
{
	if (tree_is_empty(tree) || tree->right != NULL)
	{
		ft_putendl_error("Error tree push right");
		return (0);
	}
	tree->right = sub_tree;
	return (1);
}
