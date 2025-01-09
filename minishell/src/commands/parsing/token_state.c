/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:17:09 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/09 19:26:16 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "commands.h"

t_tree	*state_redir(t_tree *tree, t_queue *queue)
{
	t_token_name	next_token_name;

	tree = add_new_token(tree, queue);
	if (tree == NULL || queue_is_empty(queue))
		return (tree);
	next_token_name = queue_first_name(queue);
	if (next_token_name == TOKEN_CMD || next_token_name == TOKEN_PIPE)
	{
		if (next_token_name == TOKEN_CMD)
			return (state_cmd(tree, queue));
		return (state_pipe(tree, queue));
	}
	else if (next_token_name == TOKEN_PAR_OPEN)
	{
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}

t_tree	*state_cmd(t_tree *tree, t_queue *queue)
{
	t_token_name	next_token_name;

	tree = add_new_token(tree, queue);
	if (tree == NULL || queue_is_empty(queue))
		return (tree);
	next_token_name = queue_first_name(queue);
	if (next_token_name == TOKEN_PIPE)
		return (state_pipe(tree, queue));
	else if (next_token_name == TOKEN_PAR_OPEN)
	{
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}

t_tree	*state_pipe(t_tree *tree, t_queue *queue)//
{
	t_token_name	type;
	t_tree			*sub_tree;

	tree = add_new_token(tree, queue);
	if (!tree)
		return (NULL);
	if (queue_is_empty(queue))
	{
		ft_putendl_error("to define");
		//print_error_token("|");// no heardoc ?
		tree_clear(&tree);
		return (NULL);
	}
	type = queue_first_name(queue);
	sub_tree = common_state(NULL, queue, type);
	if (!sub_tree)
	{
		tree_clear(&tree);
		return (NULL);
	}
	tree_push_right(tree, sub_tree);
	return (tree);
}

t_tree	*state_ope(t_tree *tree, t_queue *queue)//
{
	if (!tree)
	{
		print_error_token(queue);
		return (NULL);
	}
	tree = state_pipe(tree, queue);
	return (tree);
}

t_tree	*state_par_open(t_tree *tree, t_queue *queue)
{
	t_token_name	type;

	if (!tree_is_empty(tree) || queue_is_empty(queue))
	{
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	remove_token(queue);
	type = queue_first_name(queue);
	while (type != TOKEN_PAR_CLOSE)
	{
		tree = next_state(tree, queue);
		if (tree == NULL)
			return (NULL);
		type = queue_first_name(queue);
	}
	if (tree_is_empty(tree))
	{
		print_error_token(queue);
		return (NULL);
	}
	remove_token(queue);
	return (tree);
}
