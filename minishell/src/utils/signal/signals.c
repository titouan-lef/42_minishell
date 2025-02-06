/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:33:12 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/06 13:21:06 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	default_sigaction(struct sigaction *act)
{
	int	is_error;

	act->sa_handler = SIG_DFL;
	is_error = sigaction(SIGINT, act, NULL);
	if (is_error)
		return (is_error);
	is_error = sigaction(SIGQUIT, act, NULL);
	if (is_error)
		return (is_error);
	is_error = sigaction(SIGTSTP, act, NULL);
	if (is_error)
		return (is_error);
	is_error = sigaction(SIGPIPE, act, NULL);
	if (is_error)
		return (is_error);
	return (is_error);
}

int	modify_sigaction(struct sigaction *act, void (*f)(int), int ignore_sigquit)
{
	int	is_error;

	act->sa_handler = f;
	is_error = sigaction(SIGINT, act, NULL);
	if (is_error)
		return (is_error);
	if (ignore_sigquit)
		act->sa_handler = SIG_IGN;
	is_error = sigaction(SIGQUIT, act, NULL);
	if (is_error)
		return (is_error);
	act->sa_handler = SIG_IGN;
	is_error = sigaction(SIGTSTP, act, NULL);
	if (is_error)
		return (is_error);
	is_error = sigaction(SIGPIPE, act, NULL);
	if (is_error)
		return (is_error);
	return (is_error);
}
