/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:58:45 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/27 18:34:01 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execution.h"
#include "display.h"

static void clean(t_data *data)
{
	clear_data(data);
	ft_clean_matrix((void **)data->env);
	rl_clear_history();
}

void	my_exit(char **cmd, t_data *data, int is_piped)
{
	char exit_status;

	if (!is_piped)
		ft_printf_fd(2, "exit\n");
	if (cmd == NULL || cmd[1] == NULL)
	{
		clean(data);
		exit(0);
	}
	if (cmd[2] != NULL)
	{
		ft_printf_fd(2, "%s: exit: too many arguments\n", NAME);
		clean(data);
		return ;
	}
	exit_status = ft_atoi(cmd[1]);
	clean(data);
	exit(exit_status);
}
