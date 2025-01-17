/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:52:30 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/17 18:19:34 by tle-floc         ###   ########.fr       */
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

	ft_printf("ope token gauche : %d\n", tree->left->token.name);
	result = tree_execution(data, tree->left, 0);
	ft_printf("ope token droite : %d\n", tree->right->token.name);
	if (ft_strcmp(token.value[0], "&&") == 0)
		result = and_execution(data, tree, is_piped, result);
	else
		result = or_execution(data, tree, is_piped, result);
	if (is_piped)
		exit_exec(data, result);
	return (result);
}
