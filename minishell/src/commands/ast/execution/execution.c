/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:53:05 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/29 16:26:53 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "display.h"

void	clear_data(t_data *data)
{
	tree_clear(&data->tree);
	clear_here_docs(data->lst);
}

void	exit_exec(t_data *data, int code)
{
	ft_clean_matrix((void **)data->env);
	clear_data(data);
	rl_clear_history();
	exit(code);
}

int	tree_exec(t_data *data, t_tree *tree, int is_piped)
{
	t_token	*token;
	int		result;

	token = &tree->token;
	if (token->name == TOKEN_CMD)
		result = cmd_exec(data, token, is_piped);
	else if (token->name == TOKEN_PIPE)
		result = pipe_exec(data, tree);
	else
		result = ope_exec(data, tree, *token, is_piped);
	return (result);
}

int	make_execution(t_queue *queue, t_data *data)
{
	int	result;
	int	result2;

	if (queue_is_empty(queue))
		return (0);
	result = get_tree_data(queue, data);
	result2 = read_here_docs(data->lst, data->env);
	if (result || result2)
	{
		clear_data(data);
		if (result == 0)
			return (result2);
		return (result);
	}
	if (modify_sigaction(&data->act, cmd_display_handler))//here ?
	{
		clear_data(data);
		return (1);
	}
	result = tree_exec(data, data->tree, 0);
	clear_data(data);
	return (result);
}
