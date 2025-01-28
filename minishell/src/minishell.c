/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:34:29 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/28 10:03:05 by lguerbig         ###   ########.fr       */
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
}

static void	init_minishell(t_data *data, char **envp)
{
	ft_bzero(&data->act, sizeof(struct sigaction));
	if (modify_sigaction(&data->act, interactive_mode_handler))
		exit(1);
	data->env = strdup_tab(envp);
	if (!data->env)
	{
		ft_putendl_error(ERR_MALLOC);
		exit(1);
	}
	data->last_exit = 0;
}

static void	exit_minishell(int code, t_data *data)
{
	ft_clean_matrix((void **)data->env);
	rl_clear_history();
	ft_putendl_error("exit");
	exit(code);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line_read;
	t_data	data;

	(void)argc;
	(void)argv;
	init_minishell(&data, envp);
	while (1)
	{
		line_read = rl_gets();
		if (!line_read)
			break ;
		process_cmd(line_read, &data);
		if (modify_sigaction(&data.act, interactive_mode_handler))
			exit_minishell(1, &data);
		free(line_read);
	}
	exit_minishell(0, &data);
}
