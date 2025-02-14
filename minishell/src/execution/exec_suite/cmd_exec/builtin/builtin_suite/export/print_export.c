/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:57:15 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/13 20:14:15 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
* Goal: Print env export.
*/
void	print_export(char **env)
{
	int	i;
	int	j;

	i = 0;
	ft_insertion_qsort(env, size_tab(env), sizeof(char *), ft_void_strcmp);
	while (env[i])
	{
		j = 0;
		ft_putstr("declare -x ");
		while (env[i][j] && env[i][j] != '=')
			ft_putchar(env[i][j++]);
		if (env[i][j])
			ft_printf("=\"%s\"\n", env[i] + j + 1);
		else
			ft_putchar('\n');
		i++;
	}
}
