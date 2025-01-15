/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:49:28 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/15 17:15:37 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	make_redirs(t_token token)// todo : call good function
{
	(void) token;
	return (0);
}

static int	make_cmd(t_token token, int is_piped)// todo : call good function
{
	(void) token;
	(void) is_piped;
	return (0);
}

int	redir_execution(t_tree *data, t_token token, int is_piped)
{
	int	result;

	result = make_redirs(token);
	if (is_piped)
	{
		data_clear(data);
		exit(result);
	}
	return (result);
}

int	cmd_execution(t_tree *data, t_tree *tree, t_token token, int is_piped)
{
	int	result;

	if (tree->left != NULL)
	{
		result = tree_execution(data, tree->left, 0);
		if (result != 0)
		{
			if (is_piped)
			{
				data_clear(data);
				exit(result);
			}
			return (result);
		}
	}
	result = make_cmd(token, is_piped);//todo revoir
	if (is_piped)
	{
		data_clear(data);
		exit(result);
	}
	return (result);
}
