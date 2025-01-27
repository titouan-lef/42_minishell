/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:49:43 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/27 20:58:11 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "commands.h"

t_tree	*common_state(t_tree *tree, t_queue *queue,
		t_token_name type, t_list **here_docs)
{
	if (type == TOKEN_REDIR)
		tree = state_redir(tree, queue, here_docs);
	else if (type == TOKEN_CMD)
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

int	get_tree_data(t_queue *queue, t_data *data)
{
	//int		result;

	data->tree = NULL;
	data->lst = NULL;
	data->std[0] = -1;
	data->std[1] = -1;
	data->std[2] = -1;
	/*result = dup_data_std(data);
	if (result)
	{
		queue_clear(queue);
		return (result);
	}*/
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
