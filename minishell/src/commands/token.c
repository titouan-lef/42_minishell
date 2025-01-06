/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:31:27 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/06 17:30:36 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/*
* Goal: Create a token with a nane and a value.
*
* Return: The created token.
*
* Warning: None.
*/
t_token	token_create(t_token_name name, char **value)
{
	t_token	token;

	token.name = name;
	token.value = value;
	return (token);
}

/*
* Goal: Remove and free all the elements of the token.
*
* Return: None.
*
* Warning: token mustn't be null.
*/
void	token_clear(t_token token)
{
	ft_clean_matrix((void **)token.value);
}
