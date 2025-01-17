/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_for_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:00:40 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/17 13:13:30 by lguerbig         ###   ########.fr       */
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
	int	malloc_error;

	malloc_error = 0;
	if (redir->value)
	{
		malloc_error = queue_push(tokens, *redir);
		if (!malloc_error)
			redir->value = NULL;
	}
	if (cmd->value)
	{
		malloc_error = queue_push(tokens, *cmd);
		if (!malloc_error)
			cmd->value = NULL;
	}
	return (malloc_error);
}

static int	update(t_token *token, t_token *cmd,
		t_token *redir, t_queue *reorganized_tokens)
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
		redir->value = tab_join_and_free(redir->value, token->value);
		malloc_error = (redir->value == NULL);
	}
	if (malloc_error)
		ft_putendl_error("malloc error");
	if (token->name != TOKEN_WORD && token->name != TOKEN_REDIR)
	{
		if (push_redir_cmd(reorganized_tokens, redir, cmd))
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
		if (update(&token, &cmd, &redir, &reorganized_tokens))
		{
			token_clear(cmd);
			token_clear(redir);
			queue_clear(&tokens);
			queue_clear(&reorganized_tokens);
			return (reorganized_tokens);
		}
	}
	if (push_redir_cmd(&reorganized_tokens, &redir, &cmd))
		queue_clear(&reorganized_tokens);
	return (reorganized_tokens);
}

t_token	split_command(t_queue tokens)
{
	t_token	token;
	t_token	new_token;

	new_token = token_create(TOKEN_CMD, NULL);
	while (!queue_is_empty(&tokens))
	{
		token = queue_pop(&tokens);
		new_token.name = token.name;
		new_token.value = tab_join_and_free(new_token.value, token.value);
		if (new_token.value == NULL)
		{
			ft_putendl_error("malloc error");
			token_clear(token);
			token_clear(new_token);
			queue_clear(&tokens);
			return (new_token);
		}
	}
	queue_clear(&tokens);
	return (new_token);
}
