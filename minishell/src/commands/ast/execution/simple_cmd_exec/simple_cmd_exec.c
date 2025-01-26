/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:49:28 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/26 17:31:49 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
* Goal: Execute all the redirection of the given token.
*
* Return: O if no error, or the error code corresponding.
*
* Warning: token and data must not be null.
*/
int	redir_exec(t_data *data, t_token *token, int is_piped)
{
	int	result;

	result = expand(token, data);
	if (result)
		return (result);
	result = redir_manager(*token, data->lst);
	if (is_piped)
		exit_exec(data, result);
	return (result);
}

/*
* Goal: Execute the command of the given token.
*
* Return: O if no error, or the error code corresponding.
*
* Warning: token, tree and data must not be null.
*/
int	cmd_exec(t_data *data, t_tree *tree, t_token *token, int is_piped)
{
	int	result;

	if (tree->left != NULL)
	{
		result = tree_exec(data, tree->left, 0);
		if (result != 0)
		{
			if (is_piped)
				exit_exec(data, result);
			return (result);
		}
	}
	result = expand(token, data);
	if (result)
		return (result);
	result = cmd_manager(*token, data, is_piped);
	if (is_piped)
		exit_exec(data, result);
	return (result);
}
