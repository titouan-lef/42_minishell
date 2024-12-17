/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:35:22 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/17 15:36:31 by lguerbig         ###   ########.fr       */
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
void	export(char **str, char **env_local, char **env_export)
{
	char	*pwd;
	char	*no_error;

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