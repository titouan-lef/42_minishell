/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:23:35 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/19 17:35:22 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

typedef enum e_token_name
{
	TOKEN_PIPE,
	TOKEN_PAR,
	TOKEN_WORD,
	TOKEN_REDIR,
	TOKEN_OPE,
	TOKEN_CMD
} t_token_name;

typedef struct s_token
{
	t_token_name	name;
	char			**value;
}	t_token;

typedef struct s_element
{
	t_token			token;
	struct s_elemnt	*next;
}	t_element;

typedef struct s_queue
{
	t_element	*head;
	t_element	*tail;
}	t_queue;



#endif