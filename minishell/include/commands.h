/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:40:20 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/28 15:49:50 by tle-floc         ###   ########.fr       */
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
	char				**env;
	int					last_exit;
	t_tree				*tree;
	t_list				*lst;
	int					fd[2];
	int					std[3]; //0 -> stdin | 1 -> stdout | 2 -> stderr
	struct sigaction	act;
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
int				get_tree_data(t_queue *queue, t_data *data);

/*---token_state.c---*/
t_tree			*state_redir(t_tree *tree, t_queue *queue, t_list **here_docs);
t_tree			*state_cmd(t_tree *tree, t_queue *queue, t_list **here_docs);
t_tree			*state_junction_ope(t_tree *tree, t_queue *queue,
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
int				get_quote(const char *input, int *index, char c);
int				cmp_and_inc(const char *input, int *index, char c,
					char *buffer);
t_token_name	get_token( char *input, int *index, char *buffer);

/*---lexer.c---*/
t_queue			tokenizer(char *input);

/*---format_for_ast.c---*/
t_queue			reorganize(t_queue *tokens);
t_token			split_command(t_queue tokens);

/*---expansions.c---*/
int				expand(char ***value, t_data *data, int is_redir);
int				expand_exit_status(char ***value, int last_exit);
int				value_length_quoted(char *value);
void			quote_value(char *value, char *quoted_value, int *i);
int				update_env_var(char **word, char *new_word,
					int *letter, char **env);
char			*replace_word_env(char *word, char **env_local,
					int here_doc, int redir);
int				new_word_lenght(char *word, char **env_local);
int				expand_env_var(char ***value, char **env, int is_redir);
t_list			*find_matches(char *patern);
char			*replace_word_wildcard(char *patern);
int				expand_wildcard(char ***value);
char			*replace_word_quotes(char *word);
int				remove_quotes(char ***value);

/*---compare.c---*/
int				compare_lexicographicly(char char1, char char2);
int				strcmp_lexicographicly(const void *p1, const void *p2);

/*---cmd_manager.c---*/
int				cmd_manager(t_token token, t_data *data, int is_piped);
int				update_cmd_path(char **path, char *cmd_name, char **env);

/*---dup_utils.c---*/
int				dup_data_std(t_data *data);
int				dup2_data_std(t_data *data);
void			close_data_std(t_data *data);

#endif
