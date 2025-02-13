/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:53:21 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/13 11:26:53 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	g_sig_receive = 0;

/*
* Goal: Get the value of the received signal.
*
* Return: 0 if no signal, 128 + sig in case of signal.
*/
int	get_signal_receive(void)
{
	int	tmp;

	tmp = g_sig_receive;
	g_sig_receive = 0;
	return (tmp);
}

/*
* Goal: Detect SIGINT (Ctrl + C) and SIGQUIT (Ctrl + \).
*	- SIGINT :
*		- Move to new line.
*		- Start to read new line which start like the old (allows the old
*		line to be displayed).
*		- Clear the line (allows to doesn't start like the old line).
*		- Update display to show prompt without wait that the user write
*		in terminal.
*/
void	interactive_mode_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_receive = 128 + SIGINT;
		ft_putendl_error("");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
* Goal: Detect SIGINT (Ctrl + C) and SIGQUIT (Ctrl + \).
*	- SIGINT :
*		- Move to new line.
*	- SIQUIT :
*		- Print "Quit" and move to new line.
*/
void	cmd_display_handler(int sig)
{
	g_sig_receive = 128 + sig;
	if (sig == SIGINT)
		ft_putendl_error("");
	else if (sig == SIGQUIT)
		ft_putendl_error("Quit");
}

/*
* Goal: Detect SIGINT (Ctrl + C).
*	- SIGINT :
*		- Stop readline.
*/
void	here_doc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_receive = 128 + sig;
		rl_done = 1;
	}
}
