/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:49:43 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/24 20:16:21 by lguerbig         ###   ########.fr       */
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

void	get_tree_data(t_queue *queue, t_data *data)
{
	t_tree	*tree;
	t_list	*here_docs;

	tree = NULL;
	here_docs = NULL;
	while (!queue_is_empty(queue))
	{
		tree = next_state(tree, queue, &here_docs);
		if (tree == NULL)
			break ;
	}
	queue_clear(queue);
	data->tree = tree;
	data->lst = here_docs;
	data->std[0] = dup(STDIN_FILENO); // protections
	data->std[1] = dup(STDOUT_FILENO);
	data->std[2] = dup(STDERR_FILENO);
}
