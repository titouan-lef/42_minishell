/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:53:05 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/12 15:33:42 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "here_doc.h"

/*
* Goal: Manage execution based on the current node and the pipeline status.
*/
int	tree_exec(t_data *data, t_tree *tree, int is_piped)
{
	t_token	*token;
	int		result;

	token = &tree->token;
	if (token->name == TOKEN_CMD)
	{
		result = cmd_exec(data, token, is_piped);
		data->last_exit = result;
	}
	else if (token->name == TOKEN_PIPE)
	{
		result = pipe_exec(data, tree);
		data->last_exit = result;
	}
	else
		result = ope_exec(data, tree, *token, is_piped);
	return (result);
}

/*
* Goal: Execute every commands in the tree.
*/
int	make_execution(t_data *data)
{
	int	result;

	result = tree_exec(data, data->tree, 0);
	clear_data(data);
	return (result);
}
