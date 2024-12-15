/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:06:18 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/15 20:28:03 by lguerbig         ###   ########.fr       */
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
void	echo(char **str)
{
	if (!ft_strcmp(str[1], "-n"))
		printf("%s", str[2]);
	else
		printf("%s\n", str[2]);
}