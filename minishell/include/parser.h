/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:42:16 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/06 20:23:35 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "utils.h"

int		parser(t_queue *queue, t_data *data);

/*---state---*/
t_tree	*next_state(t_tree *tree, t_queue *queue, t_list **here_docs);
t_tree	*common_state(t_tree *tree, t_queue *queue, t_token_name type,
			t_list **here_docs);
t_tree	*state_cmd(t_tree *tree, t_queue *queue, t_list **here_docs);
t_tree	*state_junction_ope(t_tree *tree, t_queue *queue, t_list **here_docs);
t_tree	*state_par_open(t_tree *sub_tree, t_queue *queue, t_list **here_docs);

/*---utils---*/
t_tree	*add_new_token(t_tree *tree, t_queue *queue);
void	remove_token(t_queue *queue);
void	print_error_token_value(char *value);
void	print_error_token(t_queue *queue);

#endif