/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:40:20 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/21 19:29:27 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include <dirent.h>
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

typedef struct s_here_doc
{
	char	*filename;
	char	*limiter;
}			t_here_doc;

typedef struct s_data
{
	t_tree	*tree;
	t_list	*lst;
	char	***env;
	int		fd[2];
	int		std[3]; //0 -> stdin | 1 -> stdout | 2 -> stderr
}			t_data;

/*---queue_primitive.c---*/
int				queue_is_empty(t_queue *queue);
int				queue_push(t_queue *queue, t_token token);
t_token			queue_pop(t_queue *queue);
void			queue_clear(t_queue *queue);
t_queue			queue_create(void);
t_token_name	queue_first_name(t_queue *queue);

/*---parsing.c---*/
t_tree			*next_state(t_tree *tree, t_queue *queue, t_list **here_docs);
t_data			get_tree_data(t_queue *queue, char ***env);

/*---token_state.c---*/
t_tree			*state_redir(t_tree *tree, t_queue *queue, t_list **here_docs);
t_tree			*state_cmd(t_tree *tree, t_queue *queue, t_list **here_docs);
t_tree			*state_junction_ope(t_tree *tree, t_queue *queue,
					t_list **here_docs);
t_tree			*state_logical_ope(t_tree *tree, t_queue *queue,
					t_list **here_docs);
t_tree			*state_par_open(t_tree *tree, t_queue *queue,
					t_list **here_docs);

/*---token_state_utils.c---*/
t_tree			*add_new_token(t_tree *tree, t_queue *queue);
void			remove_token(t_queue *queue);
void			print_error_token_value(char *value);
void			print_error_token(t_queue *queue);
t_tree			*common_state(t_tree *tree, t_queue *queue,
					t_token_name type, t_list **here_docs);

/*---get_token.c---*/
int				cmp_and_inc(const char *input, int *index, char c,
					char *buffer);
t_token_name	get_token(char *input, int *index, char *buffer);

/*---lexer.c---*/
t_queue			auto_tokenizer(char *input);

/*---format_for_ast.c---*/
t_queue			reorganize(t_queue *tokens);
t_token			split_command(t_queue tokens);

/*---expansions.c---*/
void			expand(t_token *token, char **env_local);
int				value_length_quoted(char *value);
void			quote_value(char *value, char *quoted_value, int *i);
char			*get_quoted_value(char *name, char **env_local);
char			*replace_word_env(char *word, char **env_local, int here_doc);
int				expand_env_var(t_token *token, char **env_local);
t_list			*find_matches(char *patern);
char			*replace_word_wildcard(char *patern);
int				expand_wildcard(t_token *token);
char			*replace_word_quotes(char *word);
int				remove_quotes(t_token *token);

/*---compare.c---*/
int				compare_lexicographicly(char char1, char char2);
int				strcmp_lexicographicly(const void *p1, const void *p2);

/*---execute_cmd.c---*/
int				execute_cmd(t_token token, char ***env, int is_piped);
int				get_path(char **path, char *cmd_name, char **env);
#endif
