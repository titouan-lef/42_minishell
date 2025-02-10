/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:33:12 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/10 15:47:37 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	extra_signal_sigaction(struct sigaction *act)
{
	int	is_error;

	is_error = sigaction(SIGTSTP, act, NULL);
	if (is_error)
		return (is_error);
	is_error = sigaction(SIGPIPE, act, NULL);
	return (is_error);
}

static int	signal_sigaction(struct sigaction *act, int ignore_sigquit)
{
	int	is_error;

	is_error = sigaction(SIGINT, act, NULL);
	if (is_error)
		return (is_error);
	if (ignore_sigquit)
		act->sa_handler = SIG_IGN;
	is_error = sigaction(SIGQUIT, act, NULL);
	return (is_error);
}

/*
* Goal: Reset signals to their default use.
*
* Return: 0 on success, 1 on failure.
*/
int	default_sigaction(struct sigaction *act)
{
	int	is_error;

	act->sa_handler = SIG_DFL;
	is_error = signal_sigaction(act, 0);
	if (is_error)
		return (is_error);
	is_error = extra_signal_sigaction(act);
	return (is_error);
}

/*
* Goal: Define signals handler with 'f' function.
*		'ignore_sigquit' allows to ignore SIGQUIT.
*
* Return: 0 on success, 1 on failure.
*/
int	modify_sigaction(struct sigaction *act, void (*f)(int), int ignore_sigquit)
{
	int	is_error;

	act->sa_handler = f;
	is_error = signal_sigaction(act, ignore_sigquit);
	if (is_error)
		return (is_error);
	act->sa_handler = SIG_IGN;
	is_error = extra_signal_sigaction(act);
	return (is_error);
}
