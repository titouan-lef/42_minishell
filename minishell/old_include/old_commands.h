/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:40:20 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/06 12:16:40 by tle-floc         ###   ########.fr       */
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
	char				**read_lines;
	char				**env;
	char				**env_export;
	int					last_exit;
	t_tree				*tree;
	t_list				*lst;
	int					fd[2];
	int					last_pipe;
	struct sigaction	act;
}			t_data;

char			*read_lines(t_data *data, int here_doc);

/*---queue_primitive.c---*/
int				queue_is_empty(t_queue *queue);
int				queue_push(t_queue *queue, t_token token);
t_token			queue_pop(t_queue *queue);
void			queue_clear(t_queue *queue);
t_queue			queue_create(void);
t_token_name	queue_first_name(t_queue *queue);

/*---parsing.c---*/
t_tree			*next_state(t_tree *tree, t_queue *queue, t_list **here_docs);
int				parser(t_queue *queue, t_data *data);

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

/*---get_token---*/
t_token_name	get_operator(const char *input, int *index, char *buffer);
t_token_name	get_word(const char *input, int *index, char *buffer);
t_token_name	get_redir(const char *input, int *index, char *buffer);

/*---lexer.c---*/
int				lexer(char *input, t_queue *tokens);

/*---format_for_ast.c---*/
t_queue			form_cmd(t_queue *tokens);
t_token			split_command(t_queue tokens);


///////////////////////////////////////
//             EXPANSION             //
///////////////////////////////////////
/*---env var.c---*/
char			*get_quoted_value(char *name, char **env);
char			*replace_word_env(char *word, char **env, int here_doc, int redir);
int				expand_env_var(char ***value, char **env, int is_redir);



/*---compare.c---*/
int				strcmp_lexicographicly(const void *p1, const void *p2);
int				ft_void_strcmp(const void *s1, const void *s2);

/*---cmd_manager.c---*/
int				cmd_manager(t_token token, t_data *data, int is_piped);
int				update_cmd_path(char **path, char *cmd_name, char **env);

/*---builtin.c---*/
int				builtin_manager(char **cmd, char **redir, t_data *data,
					int is_piped);

/*---dup_utils.c---*/
void			close_data_std(int **std);

#endif
