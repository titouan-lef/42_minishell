/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:37:06 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/06 14:39:39 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "utils.h"

int				lexer(char *input, t_queue *tokens);
t_token_name	get_operator(const char *input, int *index, char *buffer);
t_token_name	get_redir(const char *input, int *index, char *buffer);
t_token_name	get_word(const char *input, int *index, char *buffer);

#endif