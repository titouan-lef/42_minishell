/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:53:05 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/15 17:16:10 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	data_clear(t_tree *data)
{
	tree_clear(&data);
}

int	tree_execution(t_tree *data, t_tree *tree, int is_piped)
{
	t_token	token;
	int		result;

	token = tree->token;
	if (token.name == TOKEN_REDIR)
		result = redir_execution(data, token, is_piped);
	if (token.name == TOKEN_CMD)
		result = cmd_execution(data, tree, token, is_piped);
	if (token.name == TOKEN_PIPE)
		result = pipe_execution(data, tree);
	else
		result = ope_execution(data, tree, token, is_piped);
	return (result);
}

int	make_execution(t_tree *data)
{
	int	result;

	result = tree_execution(data, data, 0);
	return (result);
}
