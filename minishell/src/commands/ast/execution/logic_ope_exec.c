/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_ope_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:52:30 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/27 20:33:04 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	and_exec(t_data *data, t_tree *tree, int is_piped, int result)
{
	int	result2;

	if (result != 0)
	{
		if (is_piped)
			exit_exec(data, result);
		return (result);
	}
	result = dup_data_std(data);
	if (result)
		return (result);
	result = tree_exec(data, tree->right, 0);
	result2 = dup2_data_std(data);
	close_data_std(data);
	if (result2)
		return (result2);
	return (result);
}

static int	or_exec(t_data *data, t_tree *tree, int is_piped, int result)
{
	int	result2;

	if (result == 0)
	{
		if (is_piped)
			exit_exec(data, result);
		return (result);
	}
	result = dup_data_std(data);
	if (result)
		return (result);
	result = tree_exec(data, tree->right, 0);
	result2 = dup2_data_std(data);
	close_data_std(data);
	if (result2)
		return (result2);
	return (result);
}

int	ope_exec(t_data *data, t_tree *tree, t_token token, int is_piped)
{
	int	result;
	int	result2;

	result = dup_data_std(data);
	if (result)
		return (result);
	result = tree_exec(data, tree->left, 0);
	result2 = dup2_data_std(data);
	close_data_std(data);
	if (result2)
		return (result2);
	if (ft_strcmp(token.value[0], "&&") == 0)
		result = and_exec(data, tree, is_piped, result);
	else
		result = or_exec(data, tree, is_piped, result);
	if (is_piped)
		exit_exec(data, result);
	return (result);
}
