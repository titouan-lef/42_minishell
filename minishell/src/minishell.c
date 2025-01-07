/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:34:29 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/07 15:39:31 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
// include the commands and token headers (.h)

static void	execute_cmd(char *input, char **envp)
{
	t_queue		tokens;
	t_queue		reorganized_tokens;

	if (*input)
	{
		if (!valid_parenthesis(input))
			return ;
		tokens = auto_tokenizer(input);
		reorganized_tokens = reorganize(tokens);
		if (!replace_env_var(&reorganized_tokens, envp))
		{
			printf("malloc error\n");
			queue_clear(&reorganized_tokens);
			return ;
		}
		print_tokens(&reorganized_tokens);
	 	queue_clear(&reorganized_tokens);
	}
	else
		reorganized_tokens = queue_create();
}

int	main(int argc, char **argv, char**envp)
{
	char		*line_read ;

	(void)argc;
	(void)argv;
	while (1)
	{
		line_read = rl_gets();
		if (!line_read)
			break ;
		execute_cmd(line_read, envp);
		free(line_read);
	}
	rl_clear_history();
	printf("exit\n");
	return (0);
}
