/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:49:28 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/28 16:11:58 by tle-floc         ###   ########.fr       */
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
int	cmd_exec(t_data *data, /*t_tree *tree,*/ t_token *token, int is_piped)
{
	int	result;

	/*if (tree->left != NULL)
	{
		result = tree_exec(data, tree->left, 0);
		if (result != 0)
		{
			if (is_piped)
				exit_exec(data, result);
			return (result);
		}
	}*/
	result = expand(&token->value, data, 0);
	if (result)
		return (result);
	result = expand(&token->redir, data, 1);
	if (result)
		return (result);
	result = cmd_manager(*token, data, is_piped);
	if (is_piped)
		exit_exec(data, result);
	return (result);
}
