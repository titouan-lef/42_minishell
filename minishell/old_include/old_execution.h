/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_execution.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:33:41 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/06 16:45:08 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/wait.h>
# include "redir.h"

typedef struct s_stack
{
	pid_t			pid;
	struct s_stack	*next;
}	t_stack;

/*--- stack_primitive.c ---*/
int		stack_is_empty(t_stack *stack);
int		stack_push(t_stack **stack, pid_t pid);
pid_t	stack_pop(t_stack **stack);
void	stack_clear(t_stack **stack);
void	stack_init(t_stack **stack);

/*--- execution.c ---*/
void	clear_data(t_data *data);
void	exit_exec(t_data *data, int code);
int		tree_exec(t_data *data, t_tree *tree, int is_piped);
int		make_execution(t_data *data);

/*--- *_exec.c ---*/
int		cmd_exec(t_data *data, t_token *token, int is_piped);
int		pipe_exec(t_data *data, t_tree *tree);
int		ope_exec(t_data *data, t_tree *tree, t_token token, int is_piped);

/*--- pipe_exec ---*/
int		first_cmd(t_data *data, t_tree *sub_tree, t_stack **stack);
int		midle_cmd(t_data *data, t_tree *sub_tree, t_stack **stack);
int		last_cmd(t_data *data, t_tree *sub_tree, t_stack **stack);

#endif
