/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:49:28 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/17 18:49:56 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	make_cmd(t_token token, int is_piped)// todo : call good function
{
	ft_printf("execute command : %s\n", token.value[0]);
	ft_printf("is_piped : %d\n", is_piped);
	return (0);
}

int	redir_execution(t_data *data, t_token token, int is_piped)
{
	int	result;

	result = make_redirs(token, data->lst);
	if (is_piped)
		exit_exec(data, result);
	return (result);
}

int	cmd_execution(t_data *data, t_tree *tree, t_token token, int is_piped)
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
	result = make_cmd(token, is_piped);//todo revoir
	if (is_piped)
		exit_exec(data, result);
	return (result);
}
