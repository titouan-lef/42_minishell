/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_state_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:16:23 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/28 18:34:16 by tle-floc         ###   ########.fr       */
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
	ft_putendl_error(ERR_MALLOC);
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
	ft_putstr_error(NAME);
	ft_putstr_error(ERR_SYNTAX_START);
	ft_putstr_error(value);
	ft_putendl_error(ERR_SYNTAX_END);
}

void	print_error_token(t_queue *queue)
{
	t_token	token;

	if (queue_is_empty(queue))
		print_error_token_value("newline");
	else
	{
		token = queue_pop(queue);
		if (token.value)
			print_error_token_value(token.value[0]);
		else
			print_error_token_value(token.redir[0]);
		token_clear(token);
	}
}
