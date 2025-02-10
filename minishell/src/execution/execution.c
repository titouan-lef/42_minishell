/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:53:05 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/10 10:53:39 by tle-floc         ###   ########.fr       */
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
* Goal: Read here doc with good signal and execute the commande line
* thanks to the tree.
*/
int	make_execution(t_data *data)
{
	int	result;

	result = modify_sigaction(&data->act, here_doc_handler, 1);
	if (result)
	{
		clear_data(data);
		return (1);
	}
	result = read_here_docs(data);
	if (modify_sigaction(&data->act, interactive_mode_handler, 1))
	{
		clear_data(data);
		return (1);
	}
	if (result)
	{
		clear_data(data);
		return (result);
	}
	result = tree_exec(data, data->tree, 0);
	clear_data(data);
	return (result);
}
