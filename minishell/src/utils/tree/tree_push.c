/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:37:17 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/06 17:08:10 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
* Goal: Add 'sub_tree' on the left part of 'tree'
*
* Return: 0 if error, 1 else
*/
void	tree_push_left(t_tree *tree, t_tree *sub_tree)
{
	if (tree_is_empty(tree) || tree->left != NULL)
	{
		ft_putendl_error("Error tree push left");
		return ;
	}
	tree->left = sub_tree;
}

/*
* Goal: Add 'sub_tree' on the right part of 'tree'
*
* Return: 0 if error, 1 else
*/
void	tree_push_right(t_tree *tree, t_tree *sub_tree)
{
	if (tree_is_empty(tree) || tree->right != NULL)
	{
		ft_putendl_error("Error tree push right");
		return ;
	}
	tree->right = sub_tree;
}
