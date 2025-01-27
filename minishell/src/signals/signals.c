/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:33:12 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/27 16:13:23 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	updata_sigaction(struct sigaction *act)
{
	int	is_error;

	is_error = sigaction(SIGQUIT, act, NULL);
	if (is_error)
	{
		ft_putendl_error("error sigation SIGQUIT");
		return (is_error);
	}
	is_error = sigaction(SIGINT, act, NULL);
	if (is_error)
	{
		ft_putendl_error("error sigation SIGINT");
		return (is_error);
	}
	return (0);
}

int	default_sigaction(struct sigaction *act)
{
	int	is_error;

	act->sa_handler = SIG_DFL;
	is_error = updata_sigaction(act);
	return (is_error);
}

int	modify_sigaction(struct sigaction *act, void (*f)(int))
{
	int	is_error;

	act->sa_handler = f;
	is_error = updata_sigaction(act);
	return (is_error);
}
