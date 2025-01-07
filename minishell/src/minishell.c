/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:34:29 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/07 10:30:11 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
// include the command and token headers

static int	execute_cmd(char *input, char **envp)
{
	t_queue		tokens;
	t_queue		reorganized_tokens;

	if (*input)
	{
		if (!valid_parenthesis(input))
			return (0);
		tokens = auto_tokenizer(input);
		reorganized_tokens = reorganize(tokens);
		if (!replace_env_var(&reorganized_tokens, envp))
		{
			printf("malloc error\n");
			queue_clear(&reorganized_tokens);
			return (0);
		}
		print_tokens(&reorganized_tokens);
		queue_clear(&reorganized_tokens);
	}
	else
		reorganized_tokens = queue_create();
	free(input);
	if (reorganized_tokens.head == NULL)
		return (0);
	return (1);
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
		if (execute_cmd(line_read, envp) == 0)
			continue ;
	}
	rl_clear_history();
	printf("exit\n");
	return (0);
}
