/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:28:50 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/06 18:29:51 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "here_doc.h"

void	clear_data(t_data *data)
{
	tree_clear(&data->tree);
	clear_here_docs(data->lst);
}

void	exit_exec(t_data *data, int code)
{
	if (data->read_lines)
		ft_clean_matrix((void **)data->read_lines);
	ft_clean_matrix((void **)data->env);
	ft_clean_matrix((void **)data->env_export);
	clear_data(data);
	rl_clear_history();
	exit(code);
}
