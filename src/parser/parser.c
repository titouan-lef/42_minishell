/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:49:43 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/13 19:06:36 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "here_doc.h"

/*
* Goal: Push the tokens redir and cmd in the given token queue
*		if they are not empty.
*
* Return: 0 on success, 1 on failure.
*/
static int	push_redir_cmd(t_queue *tokens, t_token *cmd)
{
	int	malloc_error;

	malloc_error = 0;
	if (cmd->value || cmd->redir)
	{
		malloc_error = queue_push(tokens, *cmd);
		if (!malloc_error)
		{
			cmd->value = NULL;
			cmd->redir = NULL;
		}
	}
	return (malloc_error);
}

/*
* Goal: Add the token.value from WORD and REDIR in the token cmd.
*		Push the token cmd  and the token in the queue if the detected token
*		is neither a WORD or a REDIR.
*
* Return: 0 on success, 1 on failure.
*/
static int	update(t_token *token, t_token *cmd, t_queue *reorganized_tokens)
{
	int	malloc_error;

	malloc_error = 0;
	if (token->name == TOKEN_WORD)
	{
		cmd->value = tab_join_and_free(cmd->value, token->value);
		malloc_error = (cmd->value == NULL);
	}
	else if (token->name == TOKEN_REDIR)
	{
		cmd->redir = tab_join_and_free(cmd->redir, token->value);
		malloc_error = (cmd->redir == NULL);
	}
	if (malloc_error)
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
	else if (token->name != TOKEN_WORD && token->name != TOKEN_REDIR)
	{
		if (push_redir_cmd(reorganized_tokens, cmd))
			malloc_error = 1;
		if (queue_push(reorganized_tokens, *token))
			malloc_error = 1;
	}
	return (malloc_error);
}

/*
* Goal: Groups the word and redir tokens into cmd token.
*
* Return: The reorganized queue.
*/
static t_queue	form_cmd(t_queue *tokens)
{
	t_queue	reorganized_tokens;
	t_token	token;
	t_token	cmd;

	cmd = token_create(TOKEN_CMD, NULL, NULL);
	reorganized_tokens = queue_create();
	while (!queue_is_empty(tokens))
	{
		token = queue_pop(tokens);
		if (update(&token, &cmd, &reorganized_tokens))
		{
			token_clear(cmd);
			queue_clear(tokens);
			queue_clear(&reorganized_tokens);
			return (reorganized_tokens);
		}
	}
	if (push_redir_cmd(&reorganized_tokens, &cmd))
		queue_clear(&reorganized_tokens);
	return (reorganized_tokens);
}

static int	exit_parser(t_queue *queue, t_data *data, int result)
{
	int	result2;

	if (result)
		clear_here_docs(data->here_docs);
	queue_clear(queue);
	result2 = get_signal_receive();
	reset_signal_receive();
	if (modify_sigaction(&data->act, interactive_mode_handler, 1))
		return (1);
	if (result2)
		return (result2);
	return (result);
}

/*
* Goal: Parse every element of the queue and built the tree for execution.
* Heredocs and signals associated are managed here.
*
* Return: 0 on success, 1 if malloc error or sigaction failed
* and 2 if syntax error.
*/
int	parser(t_queue *queue, t_data *data)
{
	int	result;

	*queue = form_cmd(queue);
	if (queue_is_empty(queue))
		return (1);
	if (modify_sigaction(&data->act, here_doc_handler, 1))
	{
		queue_clear(queue);
		return (1);
	}
	data->tree = NULL;
	data->here_docs = NULL;
	result = 0;
	while (!result && !queue_is_empty(queue))
	{
		data->tree = next_state(data->tree, queue, data);
		if (tree_is_empty(data->tree))
			result = 2;
	}
	result = exit_parser(queue, data, result);
	return (result);
}
