/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:37:17 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/04 15:43:51 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void    tree_push_left(t_tree *tree, t_tree *sub_tree)
{
	if (tree == NULL || tree->left != NULL)
    {
		ft_putendl_error("Error tree push left");
        return ;
    }
    tree->left = sub_tree;
}

void    tree_push_right(t_tree *tree, t_tree *sub_tree)
{
	if (tree == NULL || tree->right != NULL)
    {
		ft_putendl_error("Error tree push right");
        return ;
    }
    tree->right = sub_tree;
}