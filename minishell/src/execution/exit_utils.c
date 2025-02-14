/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:28:50 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/10 16:47:24 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "here_doc.h"

/*
* Goal: Clear data during execution, so clear tree and here doc list.
*/
void	clear_data(t_data *data)
{
	tree_clear(&data->tree);
	clear_here_docs(data->here_docs);
}

/*
* Goal: Clear data when the program must be exited, so clear read lines,
*		env, env export, tree, here doc list and history.
*/
void	exit_exec(t_data *data, int code)
{
	if (data->read_lines)
		ft_clean_matrix((void **)data->read_lines);
	if (data->env)
		ft_clean_matrix((void **)data->env);
	if (data->env_export)
		ft_clean_matrix((void **)data->env_export);
	clear_data(data);
	rl_clear_history();
	exit(code);
}
