/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:31:27 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/06 13:20:29 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
* Goal: Create a token with a nane and a value.
*
* Return: The created token.
*/
t_token	token_create(t_token_name name, char **value, char **redir)
{
	t_token	token;

	token.name = name;
	token.value = value;
	token.redir = redir;
	return (token);
}

/*
* Goal: Remove and free all the elements of the token.
*/
void	token_clear(t_token token)
{
	if (token.value)
		ft_clean_matrix((void **)token.value);
	if (token.redir)
		ft_clean_matrix((void **)token.redir);
}
