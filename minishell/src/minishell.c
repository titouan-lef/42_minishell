/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:34:29 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/01 18:06:59 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "execution.h"
#include "redir.h"

static void	process_cmd(char *input, t_data *data)
{
	t_queue	tokens;
	t_queue	reorganized_tokens;
	int		result;

	if (*input)
	{
		tokens = tokenizer(input);
		reorganized_tokens = reorganize(&tokens);
		result = make_execution(&reorganized_tokens, data);
		if (result)
			data->last_exit = result;
	}
	else
		data->last_exit = 0;
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
	data->last_exit = 0;
}

static void	exit_minishell(t_data *data)
{
	ft_clean_matrix((void **)data->env);
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
		line_read = rl_gets(data.env);
		code = get_signal_receive();
		if (code)
			data.last_exit = code;
		if (!line_read)
			break ;
		process_cmd(line_read, &data);
		free(line_read);
	}
	exit_minishell(&data);
}
