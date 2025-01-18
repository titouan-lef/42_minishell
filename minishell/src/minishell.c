/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:34:29 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/18 19:37:35 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
// include the commands and token headers (.h)
#include "execution.h"

static void	process_cmd(char *input, char **envp)
{
	t_queue	tokens;
	t_queue	reorganized_tokens;

	(void) envp;
	if (*input)
	{
		if (!valid_parenthesis(input))
			return ;
		tokens = auto_tokenizer(input);
		reorganized_tokens = reorganize(tokens);
		print_tokens(&reorganized_tokens);
		make_execution(&reorganized_tokens);
	}
	else
		reorganized_tokens = queue_create();
}

int	main(int argc, char **argv, char**envp)
{
	char	*line_read ;

	(void)argc;
	(void)argv;
	while (1)
	{
		line_read = rl_gets();
		if (!line_read)
			break ;
		process_cmd(line_read, envp);
		free(line_read);
		//break ;//one command
	}
	rl_clear_history();
	printf("exit\n");
	return (0);
}
