/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:53:21 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/27 18:19:08 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "display.h"

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
		ft_putstr("\n");//canal error ?
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	rl_on_new_line();
	rl_redisplay();
	ft_putstr("  \b\b");
}

void	cmd_display_handler(int sig)
{
	if (sig == SIGINT)
		ft_putstr("\n");
	else if (sig == SIGQUIT)
		ft_putstr("Quit\n");
	else
		ft_putstr("\b\b");//work only ctrl D ?
}

void	here_doc_handler(int sig)
{
	g_sig_receive = sig;
}
