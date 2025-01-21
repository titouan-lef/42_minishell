/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_state.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:17:09 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/21 17:55:05 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

t_tree	*state_redir(t_tree *tree, t_queue *queue, t_list **here_docs)
{
	t_token_name	next_token_name;

	tree = add_new_token(tree, queue);
	if (tree == NULL || queue_is_empty(queue))
		return (tree);
	detect_here_docs(tree->token, here_docs);// tree null protect
	next_token_name = queue_first_name(queue);
	if (next_token_name == TOKEN_CMD)
		tree = state_cmd(tree, queue, here_docs);
	else if (next_token_name == TOKEN_PIPE)
		tree = state_operator(tree, queue, here_docs);
	else if (next_token_name == TOKEN_PAR_OPEN)
	{
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}

t_tree	*state_cmd(t_tree *tree, t_queue *queue, t_list **here_docs)
{
	t_token_name	next_token_name;

	tree = add_new_token(tree, queue);
	if (tree == NULL || queue_is_empty(queue))
		return (tree);
	next_token_name = queue_first_name(queue);
	if (next_token_name == TOKEN_PIPE)
		tree = state_operator(tree, queue, here_docs);
	else if (next_token_name == TOKEN_PAR_OPEN)
	{
		if (tree->token.value[1] == NULL)// && tree->left == NULL --> redir
			remove_token(queue);
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}
