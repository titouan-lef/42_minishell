/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:39:26 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/22 01:46:55 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

typedef enum e_token_name
{
	TOKEN_NULL,
	TOKEN_ERROR,
	TOKEN_PIPE,
	TOKEN_PAR_OPEN,
	TOKEN_PAR_CLOSE,
	TOKEN_WORD,
	TOKEN_REDIR,
	TOKEN_OPE,
	TOKEN_CMD,
}	t_token_name;

typedef struct s_token
{
	t_token_name	name;
	char			**value;
}	t_token;

/*---token.c---*/
t_token	token_create(t_token_name name, char **value);
void	token_clear(t_token token);

#endif