/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:33:12 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/27 15:37:27 by tle-floc         ###   ########.fr       */
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
*     - Move to new line.
*     - Start to read new line which start like the old (allows the old
* line to be displayed).
*     - Clear the line (allows to doesn't start like the old line).
*     - Update display to show prompt without wait that the user write
* in terminal.
*/
static void	interactive_mode_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	rl_on_new_line();
	rl_redisplay();
	ft_putstr("  \b\b");
}

static void	cmd_display_handler(int sig)
{
	if (sig == SIGINT)
		ft_putstr("\n");
	else if (sig == SIGQUIT)
		ft_putstr("Quit\n");
	else
		ft_putstr("\b\b");//work only ctrl D ?
}

static void	here_doc_handler(int sig)
{
	g_sig_receive = sig;
}

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

int	here_doc_sigaction(struct sigaction *act)
{
	int	is_error;

	act->sa_handler = here_doc_handler;
	is_error = updata_sigaction(act);
	return (is_error);
}

int	cmd_display_sigaction(struct sigaction *act)
{
	int	is_error;

	act->sa_handler = cmd_display_handler;
	is_error = updata_sigaction(act);
	return (is_error);
}

int	default_sigaction(struct sigaction *act)
{
	int	is_error;

	act->sa_handler = SIG_DFL;
	is_error = updata_sigaction(act);
	return (is_error);
}

int	interactive_mode_sigaction(struct sigaction *act)
{
	int	is_error;

	act->sa_handler = interactive_mode_handler;
	is_error = updata_sigaction(act);
	return (is_error);
}

/*static void	spread_handler(int sig)
{
	sleep(1);
	printf("spread signal...\n");
	kill(0, sig);//protect
}

int	spread_sigaction(void)
{
	struct sigaction	act;
	int					is_error;

	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_handler = spread_handler;
	is_error = sigaction(SIGQUIT, &act, NULL);
	if (is_error)
		return (is_error);
	is_error = sigaction(SIGINT, &act, NULL);
	if (is_error)
		return (is_error);
	return (0);
}*/
