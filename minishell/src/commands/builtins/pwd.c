/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:21:18 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/18 18:14:45 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
* Goal: Equivalent of the pwd command.
*
* Return: Nothing.
*
* Warning: None.
*/
int	pwd()
{
	char	*pwd;
	char	*no_error;

	pwd = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!pwd)
		return (1);
	no_error = getcwd(pwd, PATH_MAX);
	if (no_error)
		printf("%s", pwd);
	else
		printf("\n");
	free(pwd);
	return (0);
}
