/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:06:18 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/04 18:43:11 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
* Goal: Equivalent of the echo command.
*
* Return: Nothing.
*
* Warning: None.
*/
void	echo(char **str, char **env_local)
{
	int	i;
	int	is_new_line;

	(void)env_local;
	is_new_line = 1;
	while (str[0] && str[0][0] == '-')
	{
		i = 1;
		while (str[0][i] == 'n')
			++i;
		if (str[0][i] != '\0' || i == 1)
			break ;
		is_new_line = 0;
		++str;
	}
	while (str[0])
	{
		printf("%s", str[0]);
		++str;
		if (str[0])
			printf(" ");
	}
	if (is_new_line)
		printf("\n");
}
