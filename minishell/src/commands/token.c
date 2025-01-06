/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:31:27 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/06 14:33:41 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	int	i;

	i = 0;
	while (token.value && token.value[i])
		free(token.value[i++]);
	if (token.value)
	{
		
		free(token.value);
		token.value = NULL;
	}
}