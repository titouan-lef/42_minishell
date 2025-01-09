/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:40:19 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/09 18:31:54 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "token.h"

typedef struct s_tree
{
	t_token			token;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

/* tree primitive */
int		tree_is_empty(t_tree *tree);
t_tree	*tree_add_parent(t_tree *tree, t_token token);
void	tree_clear(t_tree **tree);
t_tree	*tree_create(t_token token);

/* tree push */
void	tree_push_left(t_tree *tree, t_tree *sub_tree);
void	tree_push_right(t_tree *tree, t_tree *sub_tree);

#endif