/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:52:30 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/20 19:17:38 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	and_execution(t_data *data, t_tree *tree, int is_piped, int result)
{
	if (result != 0)
	{
		if (is_piped)
			exit_exec(data, result);
		return (result);
	}
	result = tree_execution(data, tree->right, 0);
	return (result);
}

static int	or_execution(t_data *data, t_tree *tree, int is_piped, int result)
{
	if (result == 0)
	{
		if (is_piped)
			exit_exec(data, result);
		return (result);
	}
	result = tree_execution(data, tree->right, 0);
	return (result);
}

int	ope_execution(t_data *data, t_tree *tree, t_token token, int is_piped)
{
	int	result;

	result = tree_execution(data, tree->left, 0);
	if (ft_strcmp(token.value[0], "&&") == 0)
		result = and_execution(data, tree, is_piped, result);
	else
		result = or_execution(data, tree, is_piped, result);
	if (is_piped)
		exit_exec(data, result);
	return (result);
}
