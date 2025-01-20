/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:53:05 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/20 19:17:24 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	clear_data(t_data *data)
{
	tree_clear(&data->tree);
	clear_here_docs(data->lst);
}

void	exit_exec(t_data *data, int code)
{
	ft_clean_matrix((void **)*data->env);
	clear_data(data);
	exit(code);
}

int	tree_execution(t_data *data, t_tree *tree, int is_piped)
{
	t_token	*token;
	int		result;

	token = &tree->token;
	if (token->name == TOKEN_REDIR)
		result = redir_execution(data, token, is_piped);
	else if (token->name == TOKEN_CMD)
		result = cmd_execution(data, tree, token, is_piped);
	else if (token->name == TOKEN_PIPE)
		result = pipe_execution(data, tree);
	else
		result = ope_execution(data, tree, *token, is_piped);
	return (result);
}

int	make_execution(t_queue *queue, char ***env)
{
	int		result;
	t_data	data;

	if (queue_is_empty(queue))
		return (0);//Good code ???
	data = get_tree_data(queue, env);
	queue_clear(queue);
	read_here_docs(data.lst, *data.env);
	if (tree_is_empty(data.tree))
	{
		clear_data(&data);
		return (2);//Good code ???
	}
	result = tree_execution(&data, data.tree, 0);
	clear_data(&data);
	return (result);
}
