/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:40:20 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/09 20:35:58 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "tree.h"

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

/*---queue_primitive.c---*/
int				queue_is_empty(t_queue *queue);
int				queue_push(t_queue *queue, t_token token);
t_token			queue_pop(t_queue *queue);
void			queue_clear(t_queue *queue);
t_queue			queue_create(void);
t_token_name	queue_first_name(t_queue *queue);

/*---parsing.c---*/
int				valid_parenthesis(char *input);
t_tree			*next_state(t_tree *tree, t_queue *queue);
t_tree			*get_tree(t_queue *queue);

/*---token_state.c---*/
t_tree			*state_redir(t_tree *tree, t_queue *queue);
t_tree			*state_cmd(t_tree *tree, t_queue *queue);
t_tree			*state_pipe(t_tree *tree, t_queue *queue);
t_tree			*state_ope(t_tree *tree, t_queue *queue);
t_tree			*state_par_open(t_tree *tree, t_queue *queue);

/*---token_state_utils.c---*/
t_tree			*add_new_token(t_tree *tree, t_queue *queue);
void			remove_token(t_queue *queue);
void			print_error_token(t_queue *queue);
t_tree			*common_state(t_tree *tree, t_queue *queue, t_token_name type);

/*---get_token.c---*/
t_token_name	get_token(char *input, int *index, char *buffer);

/*---lexer.c---*/
t_queue			auto_tokenizer(char *input);

/*---format_for_ast.c---*/
t_queue			reorganize(t_queue tokens);

/*---expansions.c---*/
int				expand(t_token *token);
int				expand_env_var(t_token *token, char **env_local);
int				remove_quotes(t_token *token);

#endif