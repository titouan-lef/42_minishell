/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:33:41 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/19 18:31:12 by lguerbig         ###   ########.fr       */
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

/*---stack_primitive.c---*/
int		stack_is_empty(t_stack *stack);
int		stack_push(t_stack **stack, pid_t pid);
pid_t	stack_pop(t_stack **stack);
void	stack_clear(t_stack **stack);
void	stack_init(t_stack **stack);

/*---execution.c---*/
void	exit_exec(t_data *data, int code);
int		tree_execution(t_data *data, t_tree *tree, int is_piped);
int		make_execution(t_queue *queue, char **env);

/*---*_execution.c---*/
int		redir_execution(t_data *data, t_token token, int is_piped);
int		cmd_execution(t_data *data, t_tree *tree, t_token token, int is_piped);
int		pipe_execution(t_data *data, t_tree *tree);
int		ope_execution(t_data *data, t_tree *tree, t_token token, int is_piped);

#endif
