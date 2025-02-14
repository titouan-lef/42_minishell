/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:16:23 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/10 14:47:56 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
* Goal: Adds the token of the head of the queue to the root of the tree.
*
* Warning: Funtion returns NULL if malloc fails.
*		Queue mustn't be NULL.
*/
t_tree	*add_new_token(t_tree *tree, t_queue *queue)
{
	t_tree	*parent;
	t_token	token;

	token = queue_pop(queue);
	parent = tree_add_parent(tree, token);
	if (tree_is_empty(parent))
	{
		token_clear(token);
		tree_clear(&tree);
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (NULL);
	}
	return (parent);
}

/*
* Goal: Remove the next token of the queue and free memory.
*/
void	remove_token(t_queue *queue)
{
	t_token	token;

	token = queue_pop(queue);
	token_clear(token);
}

/*
* Goal: Print the syntax error message of the token define by 'value'.
*/
void	print_error_token_value(char *value)
{
	ft_putstr_error(NAME);
	ft_putstr_error(ERR_SYNTAX_START);
	ft_putstr_error(value);
	ft_putendl_error(ERR_SYNTAX_END);
}

/*
* Goal: Print the syntax error message of the next token in the queue.
*		If queue is empty, the syntax error is "newline".
*/
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
