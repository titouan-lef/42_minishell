/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:21:18 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/10 13:08:45 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
* Goal: Prints the actuals worinkg dirrectory.
*
* Return: 1 if getcwd failed and PWD is unset.
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
