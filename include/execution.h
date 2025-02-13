/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:34:31 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/13 20:14:54 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include "utils.h"

typedef struct s_stack
{
	pid_t			pid;
	struct s_stack	*next;
}	t_stack;

typedef enum e_redir_name
{
	INPUT,
	OUTPUT,
	OUTPUT_APPEND,
	ERROR,
}	t_redir_name;

/*--- stack_primitive.c ---*/
int		stack_is_empty(t_stack *stack);
int		stack_push(t_stack **stack, pid_t pid);
pid_t	stack_pop(t_stack **stack);
void	stack_clear(t_stack **stack);
void	stack_init(t_stack **stack);

/*---execution---*/
int		make_execution(t_data *data);
void	clear_data(t_data *data);
void	exit_exec(t_data *data, int code);
int		get_child_exit_status(int status);
int		tree_exec(t_data *data, t_tree *tree, int is_piped);

/*---logical operator---*/
int		ope_exec(t_data *data, t_tree *tree, t_token token, int is_piped);

/*---pipe---*/
int		pipe_exec(t_data *data, t_tree *tree);
int		first_cmd(t_data *data, t_tree *sub_tree, t_stack **stack);
int		midle_cmd(t_data *data, t_tree *sub_tree, t_stack **stack);
int		last_cmd(t_data *data, t_tree *sub_tree, t_stack **stack);

/*---CMD EXEC---*/
int		external_cmd_manager(char **cmd, char **redir,
			t_data *data, int is_piped);
int		cmd_exec(t_data *data, t_token *token, int is_piped);

/*---builtin---*/
void	close_data_std(int *std);
int		builtin_manager(char **cmd, char **redir, t_data *data, int is_piped);
int		cd(char **cmd, char **env);
int		goto_dir(char *dir, char **env);
int		echo(char **cmd);
int		env(char **env);
int		my_exit(char **cmd, t_data *data, int is_piped, int *std);
void	print_export(char **env);
int		export(char **cmd, char ***env_local, char ***env_export);
char	*get_from_env(char **env, char *name);
char	*get_cwd(char **env);
int		pwd(char **env);
int		unset(char **cmd, char ***env);

/*---external cmd---*/
int		update_cmd_path(char **path, char *cmd_name, char **env);

/*---redir---*/
int		redir_manager(char **redirs);
int		redirect_input(int fd, char *file_name);
int		redirect_output(int fd, char *file_name);
int		redirect_output_append_mode(int fd, char *file_name);

#endif