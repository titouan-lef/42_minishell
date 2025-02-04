/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:34:29 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/04 20:12:20 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "execution.h"
#include "redir.h"

static void	process_cmd(char *input, t_data *data)
{
	t_queue	tokens;
	t_queue	reorganized_tokens;

	if (*input)
	{
		tokens = tokenizer(input);
		reorganized_tokens = reorganize(&tokens);
		data->last_exit = make_execution(&reorganized_tokens, data);
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
	data->env_export = strdup_tab(envp);
	if (!data->env)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		ft_clean_matrix((void **)data->env);
		exit(1);
	}
	data->last_exit = 0;
}

static void	exit_minishell(t_data *data)
{
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
		line_read = rl_gets(data.env);
		code = get_signal_receive();
		if (code)
			data.last_exit = code;
		if (!line_read)
			break ;
		process_cmd(line_read, &data);
		//char **split = ft_split(line_read, '\n');//protect
		free(line_read);
		/*int i = 0;
		while (split[i])
		{
			process_cmd(split[i], &data);
			++i;
		}
		ft_clean_matrix((void **)split);*/
	}
	exit_minishell(&data);
}
