/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_state_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:16:23 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/17 17:57:19 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "commands.h"

t_tree	*add_new_token(t_tree *tree, t_queue *queue)
{
	t_tree	*tmp;
	t_token	token;

	token = queue_pop(queue);
	tmp = tree_add_parent(tree, token);
	if (tmp)
		return (tmp);
	token_clear(token);
	tree_clear(&tree);
	ft_putendl_error("error malloc");
	return (NULL);
}

void	remove_token(t_queue *queue)
{
	t_token	token;

	token = queue_pop(queue);
	token_clear(token);
}

void	print_error_token_value(char *value)
{
	ft_putstr_error("bash: syntax error near unexpected token `");
	ft_putstr_error(value);
	ft_putstr_error("'\n");
}

void	print_error_token(t_queue *queue)
{
	t_token	token;

	if (queue_is_empty(queue))
		print_error_token_value("newline");
	else
	{
		token = queue_pop(queue);
		print_error_token_value(token.value[0]);
		token_clear(token);
	}
}

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
