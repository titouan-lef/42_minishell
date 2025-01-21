/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:49:28 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/21 12:15:56 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	redir_execution(t_data *data, t_token *token, int is_piped)
{
	int	result;

	//expand
	result = make_redirs(*token, data->lst);
	if (is_piped)
		exit_exec(data, result);
	return (result);
}

int	cmd_execution(t_data *data, t_tree *tree, t_token *token, int is_piped)
{
	int	result;

	if (tree->left != NULL)
	{
		result = tree_execution(data, tree->left, 0);
		if (result != 0)
		{
			if (is_piped)
				exit_exec(data, result);
			return (result);
		}
	}
	expand(token, *data->env);
	result = execute_cmd(*token, data->env, is_piped);
	if (is_piped)
		exit_exec(data, result);
	return (result);
}
