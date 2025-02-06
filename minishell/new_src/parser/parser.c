/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:49:43 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/06 09:39:10 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "commands.h"

t_tree	*common_state(t_tree *tree, t_queue *queue,
		t_token_name type, t_list **here_docs)
{
	if (type == TOKEN_CMD)
		tree = state_cmd(tree, queue, here_docs);
	else if (type == TOKEN_PAR_OPEN)
		tree = state_par_open(tree, queue, here_docs);
	else
	{
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}

t_tree	*next_state(t_tree *tree, t_queue *queue, t_list **here_docs)
{
	t_token_name	type;

	type = queue_first_name(queue);
	if (type == TOKEN_LOGIC_OPE || type == TOKEN_PIPE)
		tree = state_junction_ope(tree, queue, here_docs);
	else
		tree = common_state(tree, queue, type, here_docs);
	return (tree);
}

int	parser(t_queue *queue, t_data *data)
{
	*queue = form_cmd(queue);
	if (queue_is_empty(queue))
		return (1);
	data->tree = NULL;
	data->lst = NULL;
	while (!queue_is_empty(queue))
	{
		data->tree = next_state(data->tree, queue, &data->lst);
		if (data->tree == NULL)
		{
			queue_clear(queue);
			return (2);
		}
	}
	return (0);
}
