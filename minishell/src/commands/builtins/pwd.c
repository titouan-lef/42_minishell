/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:21:18 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/17 15:08:56 by lguerbig         ###   ########.fr       */
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
void	pwd(char **str, char **env_local)
{
	char	*pwd;
	char	*no_error;

	(void)str;
	(void)env_local;
	pwd = (char *)malloc(sizeof(char) * PATH_MAX);
	no_error = getcwd(pwd, PATH_MAX);
	if (no_error)
		printf("%s", pwd);
	else
		printf("\n");
	free(pwd);
}