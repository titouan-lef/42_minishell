/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:58:45 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/10 13:03:23 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*
* Goal: Exit the actual processus with the preciced code in cmd[1].
*
* Return: 1 if wrong number of argument and cmd[1] is a long long.
*/
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
		ft_printf_fd(2, "%s: exit: %s: %s\n", NAME, cmd[1], ERR_NUM_ARG);
		clean(data);
		exit(2);
	}
	if (cmd[2] != NULL)
	{
		ft_printf_fd(2, "%s: exit: %s\n", NAME, ERR_NB_ARG);
		return (1);
	}
	clean(data);
	exit(exit_status);
}
