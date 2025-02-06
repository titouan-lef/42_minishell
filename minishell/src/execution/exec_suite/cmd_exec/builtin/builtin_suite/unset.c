/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:38:50 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/06 18:32:12 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
* Goal: Equivalent of the unset command.
*
* Warning: None.
*/
static int	is_var_to_unset(char *var_name, char **list)
{
	int	length;
	int	i;

	while (*list)
	{
		i = 0;
		while ((*list)[i])
		{
			if (!ft_isalnum((*list)[i]) && (*list)[i] != '_')
				break ;
			++i;
		}
		if ((*list)[i] == '\0')
		{
			length = ft_strlen(*list);
			if (!ft_strncmp(var_name, *list, length)
				&& (!var_name[length] || var_name[length] == '='))
				return (1);
		}
		list++;
	}
	return (0);
}

int	unset(char **cmd, char ***env)
{
	char	**new_env;
	int		num_var;

	if (!*(++cmd))
		return (0);
	new_env = ft_calloc(1, sizeof(char *));
	if (!new_env)
		return (1);
	num_var = 0;
	while ((*env)[num_var])
	{
		if (!is_var_to_unset((*env)[num_var], cmd))
		{
			new_env = append_to_tab(new_env, (*env)[num_var]);
			if (!new_env)
			{
				ft_printf_fd(2, "%s: %s", NAME, ERR_MALLOC);
				return (1);
			}
		}
		num_var++;
	}
	ft_clean_matrix(*(void ***)env);
	*env = new_env;
	return (0);
}
