/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:14:40 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/03 11:41:45 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	dup_data_std(t_data *data)
{
	data->std[0] = dup(STDIN_FILENO);
	if (data->std[0] < 0)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_DUP);
		data->std[1] = -1;
		data->std[2] = -1;
		return (1);
	}
	data->std[1] = dup(STDOUT_FILENO);
	if (data->std[1] < 0)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_DUP);
		data->std[2] = -1;
		return (1);
	}
	data->std[2] = dup(STDERR_FILENO);
	if (data->std[2] < 0)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_DUP);
		return (1);
	}
	return (0);
}

int	dup2_data_std(t_data *data)
{
	int	result;
	int	is_error;

	is_error = 0;
	result = dup2(data->std[0], STDIN_FILENO);
	if (result < 0)
		is_error = 1;
	result = dup2(data->std[1], STDOUT_FILENO);
	if (result < 0)
		is_error = 1;
	result = dup2(data->std[2], STDERR_FILENO);
	if (result < 0)
		is_error = 1;
	if (is_error)
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_DUP2);
	return (is_error);
}

void	close_data_std(t_data *data)
{
	if (data->std[0] != -1)
		close(data->std[0]);
	if (data->std[1] != -1)
		close(data->std[1]);
	if (data->std[2] != -1)
		close(data->std[2]);
	data->std[0] = -1;
	data->std[1] = -1;
	data->std[2] = -1;
}
