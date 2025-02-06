/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:21:18 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/06 18:32:08 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
* Goal: Equivalent of the pwd command.
*
* Return: Nothing.
*
* Warning: None.
*/
int	pwd(char **env)
{
	char	*pwd;

	pwd = get_cwd(env);
	if (pwd == NULL)
		return (1);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}
