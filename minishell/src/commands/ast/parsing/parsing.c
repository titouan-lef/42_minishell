/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:49:43 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/21 16:44:41 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "commands.h"

t_tree	*next_state(t_tree *tree, t_queue *queue, t_list **here_docs)
{
	t_token_name	type;

	type = queue_first_name(queue);
	if (type == TOKEN_OPE)
		tree = state_ope(tree, queue, here_docs);
	else
		tree = common_state(tree, queue, type, here_docs);
	return (tree);
}

t_data	get_tree_data(t_queue *queue, char ***env)
{
	t_tree	*tree;
	t_list	*here_docs;
	t_data	data;

	tree = NULL;
	here_docs = NULL;
	while (!queue_is_empty(queue))
	{
		tree = next_state(tree, queue, &here_docs);
		if (tree == NULL)
			break ;
	}
	queue_clear(queue);
	data.tree = tree;
	data.lst = here_docs;
	data.env = env;
	data.std[0] = dup(STDIN_FILENO); // protections
	data.std[1] = dup(STDOUT_FILENO);
	data.std[2] = dup(STDERR_FILENO);
	return (data);
}
