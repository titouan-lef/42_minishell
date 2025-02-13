/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:46:18 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/12 12:23:56 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
* Goal: Update the 'tree' with the next "common" state define by
*		the next token of the 'queue'.
*
* Return: New tree or NULL if the next token is a ")", a "|", a "||" or a "&&".
*/
t_tree	*common_state(t_tree *tree, t_queue *queue,
	t_token_name type, t_data *data)
{
	if (type == TOKEN_CMD)
		tree = state_cmd(tree, queue, data);
	else if (type == TOKEN_PAR_OPEN)
		tree = state_par_open(tree, queue, data);
	else
	{
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}

/*
* Goal: Update the 'tree' with the next state define by
*		the next token of the 'queue'.
*
* Return: New tree or NULL if the next token is a ")".
*/
t_tree	*next_state(t_tree *tree, t_queue *queue, t_data *data)
{
	t_token_name	type;

	type = queue_first_name(queue);
	if (type == TOKEN_LOGIC_OPE || type == TOKEN_PIPE)
		tree = state_junction_ope(tree, queue, data);
	else
		tree = common_state(tree, queue, type, data);
	return (tree);
}
