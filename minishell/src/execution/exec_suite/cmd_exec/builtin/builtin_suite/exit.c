/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:58:45 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/06 16:51:59 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"
#include "input.h"
#include "execution.h"

static void	clean(t_data *data)
{
	clear_data(data);
	if (data->read_lines)
		ft_clean_matrix((void **)data->read_lines);
	ft_clean_matrix((void **)data->env);
	ft_clean_matrix((void **)data->env_export);
	rl_clear_history();
}

int	my_exit(char **cmd, t_data *data, int is_piped)
{
	char	exit_status;
	int		status;

	if (!is_piped)
		ft_printf_fd(2, "exit\n");
	if (cmd == NULL || cmd[1] == NULL)
	{
		clean(data);
		exit(0);
	}
	exit_status = (char)ft_to_number(cmd[1], &status, LLONG_MAX);
	if (status)
	{
		ft_printf_fd(2, "%s: exit: %s: numeric argument required\n", NAME, cmd[1]);
		clean(data);
		exit(2);
	}
	if (cmd[2] != NULL)
	{
		ft_printf_fd(2, "%s: exit: too many arguments\n", NAME);
		return (1);
	}
	clean(data);
	exit(exit_status);
}
