/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:58:45 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/13 18:53:44 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	clean(t_data *data, int *std)
{
	clear_data(data);
	close_data_std(std);
	if (data->read_lines)
		ft_clean_matrix((void **)data->read_lines);
	ft_clean_matrix((void **)data->env);
	ft_clean_matrix((void **)data->env_export);
	rl_clear_history();
}

static char	get_exit_status(char *param, t_data *data, int *std)
{
	size_t	i;
	int		status;
	char	exit_status;

	i = 0;
	while (ft_isspace(param[i]))
		++i;
	exit_status = (char)ft_to_number(param + i, &status, LLONG_MAX);
	if (status)
	{
		ft_printf_fd(2, "%s: exit: %s: %s\n", NAME, param, ERR_NUM_ARG);
		clean(data, std);
		exit(2);
	}
	return (exit_status);
}

/*
* Goal: Exit the actual processus with the preciced code in cmd[1].
*
* Return: 1 if wrong number of argument and cmd[1] is a long long.
*/
int	my_exit(char **cmd, t_data *data, int is_piped, int *std)
{
	char	exit_status;

	if (!is_piped)
		ft_printf_fd(2, "exit\n");
	if (cmd == NULL || cmd[1] == NULL)
	{
		clean(data, std);
		exit(data->last_exit);
	}
	exit_status = get_exit_status(cmd[1], data, std);
	if (cmd[2] != NULL)
	{
		ft_printf_fd(2, "%s: exit: %s\n", NAME, ERR_NB_ARG);
		return (1);
	}
	clean(data, std);
	exit(exit_status);
}
