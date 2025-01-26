/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:53:05 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/26 17:34:13 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	clear_data(t_data *data)
{
	tree_clear(&data->tree);
	clear_here_docs(data->lst);
	close(data->std[0]);
	close(data->std[1]);
	close(data->std[2]);
}

void	exit_exec(t_data *data, int code)
{
	close(data->fd[0]);
	close(data->fd[1]);
	ft_clean_matrix((void **)data->env);
	clear_data(data);
	exit(code);
}

int	tree_exec(t_data *data, t_tree *tree, int is_piped)
{
	t_token	*token;
	int		result;

	token = &tree->token;
	if (token->name == TOKEN_REDIR)
		result = redir_exec(data, token, is_piped);
	else if (token->name == TOKEN_CMD)
		result = cmd_exec(data, tree, token, is_piped);
	else if (token->name == TOKEN_PIPE)
		result = pipe_exec(data, tree);
	else
		result = ope_exec(data, tree, *token, is_piped);
	return (result);
}

int	make_execution(t_queue *queue, t_data *data)
{
	int		result;

	if (queue_is_empty(queue))
		return (0);//Good code ???
	get_tree_data(queue, data);
	queue_clear(queue);
	read_here_docs(data->lst, data->env); //protections
	if (tree_is_empty(data->tree))
	{
		clear_data(data);
		return (2);//Good code ???
	}
	result = tree_exec(data, data->tree, 0);
	dup2(data->std[0], STDIN_FILENO); //protections
	dup2(data->std[1], STDOUT_FILENO);
	dup2(data->std[2], STDERR_FILENO);
	clear_data(data);
	return (result);
}
