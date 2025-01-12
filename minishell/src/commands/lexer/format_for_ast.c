/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_for_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:00:40 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/12 12:00:36 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

/*
* Goal: Push the tokens redir and cmd in the given token queue
*		if they are not empty.
*
* Warning: token, redir and cmd must not be null.
*/
static int	push_redir_cmd(t_queue *tokens, t_token *redir, t_token *cmd)
{
	int	malloc_succes;

	malloc_succes = 1;
	if (redir->value)
	{
		malloc_succes = queue_push(tokens, *redir);
		if (malloc_succes)
			redir->value = NULL;
	}
	if (cmd->value)
	{
		malloc_succes = queue_push(tokens, *cmd);
		if (malloc_succes)
			cmd->value = NULL;
	}
	return (malloc_succes);
}

static int	update(t_token *token, t_token *cmd, t_token *redir, t_queue *r_tk)
{
	int	malloc_succes;

	malloc_succes = 1;
	if (token->name == TOKEN_WORD)
	{
		cmd->value = tab_join_and_free(cmd->value, token->value);
		malloc_succes = (cmd->value != NULL);
	}
	else if (token->name == TOKEN_REDIR)
	{
		redir->value = tab_join_and_free(redir->value, token->value);
		malloc_succes = (redir->value != NULL);
	}
	if (!malloc_succes)
		printf("malloc error\n");
	if (token->name != TOKEN_WORD && token->name != TOKEN_REDIR)
	{
		if (!push_redir_cmd(r_tk, redir, cmd))
			malloc_succes = 0;
		if (!queue_push(r_tk, *token))
			malloc_succes = 0;
	}
	return (malloc_succes);
}

/*
* Goal: Groups the word and redir tokens.
*
* Return: The reorganized queue.
*
* Warning: token must not be null.
*/
t_queue	reorganize(t_queue tokens)
{
	t_queue	reorganized_tokens;
	t_token	token;
	t_token	cmd;
	t_token	redir;

	cmd = token_create(TOKEN_CMD, NULL);
	redir = token_create(TOKEN_REDIR, NULL);
	reorganized_tokens = queue_create();
	while (!queue_is_empty(&tokens))
	{
		token = queue_pop(&tokens);
		if (!update(&token, &cmd, &redir, &reorganized_tokens))
		{
			token_clear(cmd);
			token_clear(redir);
			queue_clear(&tokens);
			queue_clear(&reorganized_tokens);
			return (reorganized_tokens);
		}
	}
	if (!push_redir_cmd(&reorganized_tokens, &redir, &cmd))
		queue_clear(&reorganized_tokens);
	return (reorganized_tokens);
}

t_token	split_command(t_queue tokens)
{
	t_token	token;
	t_token	cmd;
	t_token	redir;

	cmd = token_create(TOKEN_CMD, NULL);
	redir = token_create(TOKEN_REDIR, NULL);
	while (!queue_is_empty(&tokens))
	{
		token = queue_pop(&tokens);
		if (!update(&token, &cmd, &redir, NULL))
		{
			token_clear(cmd);
			token_clear(redir);
			queue_clear(&tokens);
			return (cmd);
		}
	}
	token_clear(redir);
	queue_clear(&tokens);
	return (cmd);
}
