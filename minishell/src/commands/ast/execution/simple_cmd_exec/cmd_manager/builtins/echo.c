/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:06:18 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/01 17:46:59 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
* Goal: Equivalent of the echo command.
*
* Warning: str must not be null.
*/
int	echo(char **cmd)
{
	int	i;
	int	is_new_line;

	++cmd;
	is_new_line = 1;
	while (cmd[0] && cmd[0][0] == '-')
	{
		i = 1;
		while (cmd[0][i] == 'n')
			++i;
		if (cmd[0][i] != '\0' || i == 1)
			break ;
		is_new_line = 0;
		++cmd;
	}
	while (cmd[0])
	{
		ft_printf("%s", cmd[0]);
		++cmd;
		if (cmd[0])
			ft_printf(" ");
	}
	if (is_new_line)
		ft_printf("\n");
	return (0);
}
