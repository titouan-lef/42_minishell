/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:57:15 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/29 19:29:39 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env(char **cmd, char **env)
{
	int	i;

	(void)cmd;
	i = 0;
	//ft_insertion_qsort(env, size_tab(env), sizeof(char *), strcmp_lexicographicly);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
