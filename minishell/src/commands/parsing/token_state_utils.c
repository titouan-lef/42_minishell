/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_state_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:16:23 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/09 19:55:55 by tle-floc         ###   ########.fr       */
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

void	print_error_token(t_queue *queue)
{
	t_token	token;

	token = queue_pop(queue);
	ft_printf_fd(2, "bash: syntax error near unexpected token `%s'\n", token.value[0]);
	token_clear(token);
}

t_tree	*common_state(t_tree *tree, t_queue *queue, t_token_name type)
{
	if (type == TOKEN_REDIR)
		tree = state_redir(tree, queue);
	else if (type == TOKEN_CMD)
		tree = state_cmd(tree, queue);
	else if (type == TOKEN_PAR_OPEN)
		tree = state_par_open(tree, queue);
	else
	{
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}
