/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_operator_state.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:59:28 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/21 17:55:05 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

t_tree	*state_operator(t_tree *tree, t_queue *queue, t_list **here_docs)//
{
	t_token_name	type;
	t_tree			*sub_tree;

	tree = add_new_token(tree, queue);
	if (!tree)
		return (NULL);
	if (queue_is_empty(queue))
	{
		print_error_token_value(tree->token.value[0]);
		tree_clear(&tree);
		return (NULL);
	}
	type = queue_first_name(queue);
	sub_tree = common_state(NULL, queue, type, here_docs);
	if (!sub_tree)
	{
		tree_clear(&tree);
		return (NULL);
	}
	tree_push_right(tree, sub_tree);
	return (tree);
}

t_tree	*state_ope(t_tree *tree, t_queue *queue, t_list **here_docs)//
{
	if (!tree)
	{
		print_error_token(queue);
		return (NULL);
	}
	tree = state_operator(tree, queue, here_docs);
	return (tree);
}

t_tree	*state_par_open(t_tree *tree, t_queue *queue, t_list **here_docs)
{
	t_token_name	type;

	if (!tree_is_empty(tree) || queue_is_empty(queue))
	{
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	remove_token(queue);
	while (!queue_is_empty(queue))
	{
		type = queue_first_name(queue);
		if (type == TOKEN_PAR_CLOSE)
			break ;
		tree = next_state(tree, queue, here_docs);
		if (tree == NULL)
			return (NULL);
	}
	if (queue_is_empty(queue))
	{
		print_error_token_value("(");
		return (NULL);
	}
	if (tree_is_empty(tree))
	{
		print_error_token(queue);
		return (NULL);
	}
	remove_token(queue);
	return (tree);
}