/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:40:19 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/04 14:43:27 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

#include "minishell.h"

typedef struct s_tree
{
	t_token			token;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

#endif