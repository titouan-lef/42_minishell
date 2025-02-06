/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:13:39 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/06 18:07:26 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"

# define NAME "minishell"

/*---Error messages---*/
# define ERR_HERDOC_END "warning: here-document delimited by end-of-file"
# define ERR_HERDOC_ACC "error heredoc access"
# define ERR_MALLOC "malloc failed"
# define ERR_FORK "fork failed"
# define ERR_DUP "dup failed"
# define ERR_DUP2 "dup2 failed"
# define ERR_CLOSE "close failed"
# define ERR_NO_FILE "No such file or directory"
# define ERR_NO_PERM "Permission denied"
# define ERR_NO_CMD "Command not found"
# define ERR_SYNTAX_START ": syntax error near unexpected token `"
# define ERR_SYNTAX_END "'"
# define ERR_RND "Impossible to geneate a here_doc name"
# define ERR_EXP "not a valid identifier"

/*---token struct---*/
typedef enum e_token_name
{
	TOKEN_NULL,
	TOKEN_ERROR,
	TOKEN_PIPE,
	TOKEN_PAR_OPEN,
	TOKEN_PAR_CLOSE,
	TOKEN_WORD,
	TOKEN_REDIR,
	TOKEN_LOGIC_OPE,
	TOKEN_CMD,
}		t_token_name;

typedef struct s_token
{
	t_token_name	name;
	char			**value;
	char			**redir;
}		t_token;

/*---queue struct---*/
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

/*---tree struct---*/
typedef struct s_tree
{
	t_token			token;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

/*---data struct---*/
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
}	t_data;

/*---token---*/
t_token			token_create(t_token_name name, char **value, char **redir);
void			token_clear(t_token token);

/*---queue---*/
int				queue_is_empty(t_queue *queue);
int				queue_push(t_queue *queue, t_token token);
t_token			queue_pop(t_queue *queue);
void			queue_clear(t_queue *queue);
t_queue			queue_create(void);
t_token_name	queue_first_name(t_queue *queue);

/*---tree---*/
int				tree_is_empty(t_tree *tree);
t_tree			*tree_add_parent(t_tree *tree, t_token token);
void			tree_clear(t_tree **tree);
t_tree			*tree_create(t_token token);
void			tree_push_left(t_tree *tree, t_tree *sub_tree);
void			tree_push_right(t_tree *tree, t_tree *sub_tree);

/*---signal---*/
int				default_sigaction(struct sigaction *act);
int				modify_sigaction(struct sigaction *act, void (*f)(int), int ignore_sigquit);
void			interactive_mode_handler(int sig);
void			cmd_display_handler(int sig);
void			here_doc_handler(int sig);
int				get_signal_receive(void);

/*---tab---*/
size_t			size_tab(char **tab);
char			**strdup_tab(char **tab);
char			**tab_join(char **tab1, char **tab2);
char			**tab_join_and_free(char **tab1, char **tab2);
char			**append_to_tab(char **tab, const char *str);

/*---compare---*/
int				strcmp_lexicographicly(const void *p1, const void *p2);
int				ft_void_strcmp(const void *s1, const void *s2);

/*---path---*/
char			*get_from_env(char **env, char *name);
char			*get_cwd(char **env);

#endif