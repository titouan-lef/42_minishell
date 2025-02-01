/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:53:21 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/01 11:26:26 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "display.h"
#include <sys/ioctl.h>

int	g_sig_receive = 0;

int	get_signal_receive(void)
{
	int	tmp;

	tmp = g_sig_receive;
	g_sig_receive = 0;
	return (tmp);
}

/*
* Goal: Detect SIGINT (Ctrl + C) and SIGQUIT (Ctrl + \).
* - SIGQUIT : Remove "^\".
* - SIGINT :
*	- Move to new line.
*	- Start to read new line which start like the old (allows the old
* line to be displayed).
*	- Clear the line (allows to doesn't start like the old line).
*	- Update display to show prompt without wait that the user write
* in terminal.
*/
void	interactive_mode_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_receive = 128 + SIGINT;
		ft_putendl_error("");//canal error ? i thnik so, is solve the space probleme
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	cmd_display_handler(int sig)
{
	g_sig_receive = 128 + sig;
	if (sig == SIGINT)
		ft_putstr("\n");
	else if (sig == SIGQUIT)
		ft_putstr("Quit\n");
}

void	here_doc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_receive = 128 + sig;
		ioctl(0, TIOCSTI, "\r");
	}
}
