/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:23:35 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/06 15:09:23 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "builtins.h"

typedef enum e_token_name
{
	TOKEN_NULL,
	TOKEN_PIPE,
	TOKEN_PAR,
	TOKEN_WORD,
	TOKEN_REDIR,
	TOKEN_OPE,
	TOKEN_CMD,
}	t_token_name;

typedef struct s_token
{
	t_token_name	name;
	char			**value;
}	t_token;

typedef struct s_element
{
	t_token				token;
	struct s_element	*next;
}	t_element;

typedef struct s_queue
{
	t_element	*head;
	t_element	*tail;
}	t_queue;

/*---token.c---*/
void	token_clear(t_token token);

/*---parsing.c---*/
int		valid_parenthesis(char *input);

/*---lexer.c---*/
t_queue	auto_tokenizer(const char *input);

/*---queue_primitive.c---*/
int		queue_push(t_queue *queue, t_token token);
t_token	queue_pop(t_queue *queue);
void	queue_clear(t_queue *queue);
t_queue	queue_create(void);

/*---format_for_ast.c---*/
t_queue	reorganize(t_queue tokens);

/*---replace_env.c---*/
void	replace_env_var(t_queue *tokens, char **env_local);

#endif