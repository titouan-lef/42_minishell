/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:49:28 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/01 18:17:46 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
* Goal: Execute the command of the given token.
*
* Return: O if no error, or the error code corresponding.
*
* Warning: token, tree and data must not be null.
*/
int	cmd_exec(t_data *data, t_token *token, int is_piped)
{
	int	result;

	result = expand(&token->value, data, 0);
	if (result)
	{
		if (is_piped)
			exit_exec(data, result);
		return (result);
	}
	result = expand(&token->redir, data, 1);
	if (result)
	{
		if (is_piped)
			exit_exec(data, result);
		return (result);
	}
	result = cmd_manager(*token, data, is_piped);
	if (is_piped)
		exit_exec(data, result);
	return (result);
}
