/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:00:40 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/01 13:05:15 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Push the tokens redir and cmd in the given token queue
*		if they are not empty.
*
* Warning: token, redir and cmd must not be null.
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
		ft_printf_fd(2, "%s: %s\n" , NAME, ERR_MALLOC);
	if (token->name != TOKEN_WORD && token->name != TOKEN_REDIR)
	{
		if (push_redir_cmd(reorganized_tokens, cmd))
			malloc_error = 1;
		if (queue_push(reorganized_tokens, *token))
			malloc_error = 1;
	}
	return (malloc_error);
}

/*
* Goal: Groups the word and redir tokens.
*
* Return: The reorganized queue.
*
* Warning: token must not be null.
*/
t_queue	reorganize(t_queue *tokens)
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

t_token	split_command(t_queue tokens)//up
{
	t_token	token;
	t_token	new_token;

	new_token = token_create(TOKEN_CMD, NULL, NULL);
	while (!queue_is_empty(&tokens))
	{
		token = queue_pop(&tokens);
		new_token.value = tab_join_and_free(new_token.value, token.value);
		if (new_token.value == NULL)
		{
			ft_printf_fd(2, "%s: %s\n" , NAME, ERR_MALLOC);
			token_clear(token);
			token_clear(new_token);
			queue_clear(&tokens);
			return (new_token);
		}
	}
	queue_clear(&tokens);
	return (new_token);
}
