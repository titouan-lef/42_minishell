/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:34:29 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/24 20:34:06 by lguerbig         ###   ########.fr       */
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
		make_execution(&reorganized_tokens, data);
	}
}

int	main(int argc, char **argv, char**envp)
{
	char	*line_read;
	t_data	data;

	(void)argc;
	(void)argv;
	data.last_exit = 0;
	data.env = strdup_tab(envp);
	while (1)
	{
		line_read = rl_gets();
		if (!line_read)
			break ;
		process_cmd(line_read, &data);
		free(line_read);
	}
	ft_clean_matrix((void **)data.env);
	rl_clear_history();
	printf("exit\n");
	return (0);
}
