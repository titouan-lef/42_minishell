/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_for_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:00:40 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/07 18:21:52 by lguerbig         ###   ########.fr       */
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
		redir->value = NULL;
	}
	if (cmd->value)
	{
		malloc_succes = queue_push(tokens, *cmd);
		cmd->value = NULL;
	}
	return (malloc_succes);
}

static int	manage_tokens(t_token *tk, t_token *cmd, t_token *rdr, t_queue *rt)
{
	int	malloc_succes;

	malloc_succes = 0;
	if (tk->name == TOKEN_WORD)
	{
		cmd->value = tab_join_and_free(cmd->value, tk->value);
		malloc_succes = (cmd->value != NULL);
	}
	else if (tk->name == TOKEN_REDIR)
	{
		rdr->value = tab_join_and_free(rdr->value, tk->value);
		malloc_succes = (cmd->value != NULL);
	}
	else
	{
		push_redir_cmd(rt, rdr, cmd);
		if (! push_redir_cmd(rt, rdr, cmd)
			|| !queue_push(rt, *tk))
			malloc_succes = 0;
	}
	if (!malloc_succes)
		printf("malloc error\n");
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
	redir = token_create(TOKEN_CMD, NULL);
	reorganized_tokens = queue_create();
	while (tokens.head)
	{
		token = queue_pop(&tokens);
		if (!manage_tokens(&token, &cmd, &redir, &reorganized_tokens))
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
