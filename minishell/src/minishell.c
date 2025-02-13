/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:34:29 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/13 12:10:05 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "input.h"
#include "lexer.h"
#include "parser.h"
#include "execution.h"

static void	process_cmd(char *input, t_data *data)
{
	t_queue	tokens;
	int		result;

	result = lexer(input, &tokens);
	if (result)
	{
		data->last_exit = result;
		return ;
	}
	if (queue_is_empty(&tokens))
		return ;
	result = parser(&tokens, data);
	if (result)
	{
		data->last_exit = result;
		return ;
	}
	data->last_exit = make_execution(data);
	get_signal_receive();
}

static void	init_minishell(t_data *data, char **envp)
{
	rl_outstream = stderr;
	ft_bzero(&data->act, sizeof(struct sigaction));
	if (modify_sigaction(&data->act, interactive_mode_handler, 1))
		exit(1);
	data->env = strdup_tab(envp);
	if (!data->env)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		exit(1);
	}
	data->env_export = strdup_tab(envp);
	if (!data->env)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		ft_clean_matrix((void **)data->env);
		exit(1);
	}
	data->read_lines = NULL;
	data->last_exit = 0;
}

static void	exit_minishell(t_data *data)
{
	if (data->read_lines)
		ft_clean_matrix((void **)data->read_lines);
	ft_clean_matrix((void **)data->env);
	ft_clean_matrix((void **)data->env_export);
	rl_clear_history();
	ft_putendl_error("exit");
	exit(data->last_exit);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line_read;
	t_data	data;
	int		code;

	(void)argc;
	(void)argv;
	init_minishell(&data, envp);
	while (1)
	{
		line_read = read_lines(&data, 0);
		if (line_read && line_read[0] != '\0')
			add_history(line_read);
		code = get_signal_receive();
		if (code)
			data.last_exit = code;
		if (!line_read)
			break ;
		process_cmd(line_read, &data);
	}
	exit_minishell(&data);
}
