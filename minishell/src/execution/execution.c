/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:53:05 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/07 15:13:08 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "here_doc.h"

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

int	make_execution(t_data *data)
{
	int	result;
	int	result2;

	result = modify_sigaction(&data->act, here_doc_handler, 1);
	result2 = read_here_docs(data);
	if (result || modify_sigaction(&data->act, interactive_mode_handler, 1))
	{
		clear_data(data);
		return (1);
	}
	if (result2)
	{
		clear_data(data);
		return (result2);
	}
	result = tree_exec(data, data->tree, 0);
	clear_data(data);
	return (result);
}
