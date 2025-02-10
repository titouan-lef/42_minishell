/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_ope_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:52:30 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/10 09:50:07 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	and_exec(t_data *data, t_tree *tree, int is_piped, int result)
{
	if (result != 0)
	{
		if (is_piped)
			exit_exec(data, result);
		return (result);
	}
	result = tree_exec(data, tree->right, 0);
	return (result);
}

static int	or_exec(t_data *data, t_tree *tree, int is_piped, int result)
{
	if (result == 0)
	{
		if (is_piped)
			exit_exec(data, result);
		return (result);
	}
	result = tree_exec(data, tree->right, 0);
	return (result);
}

/*
* Goal: Execute the first command and execute the second
* according to the result of the first.
*/
int	ope_exec(t_data *data, t_tree *tree, t_token token, int is_piped)
{
	int	result;

	result = tree_exec(data, tree->left, 0);
	if (ft_strcmp(token.value[0], "&&") == 0)
		result = and_exec(data, tree, is_piped, result);
	else
		result = or_exec(data, tree, is_piped, result);
	if (is_piped)
		exit_exec(data, result);
	return (result);
}
