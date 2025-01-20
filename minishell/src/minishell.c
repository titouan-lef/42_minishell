/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:34:29 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/20 19:45:45 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
// include the commands and token headers (.h)
#include "execution.h"
#include "redir.h"

static void	process_cmd(char *input, char ***env)
{
	t_queue	tokens;
	t_queue	reorganized_tokens;
	int		save_errput;
	int		save_output;
	int		save_input;

	if (*input)
	{
		save_errput = dup(STDERR_FILENO);
		save_output = dup(STDOUT_FILENO);
		save_input = dup(STDIN_FILENO);
		if (!valid_parenthesis(input))
			return ;
		tokens = auto_tokenizer(input);
		reorganized_tokens = reorganize(tokens);
		make_execution(&reorganized_tokens, env);
		dup2(save_errput, STDERR_FILENO);
		dup2(save_output, STDOUT_FILENO);
		dup2(save_input, STDIN_FILENO);
		close(save_errput);
		close(save_output);
		close(save_input);
	}
}

int	main(int argc, char **argv, char**envp)
{
	char	*line_read;
	char	**env;

	(void)argc;
	(void)argv;
	env = strdup_tab(envp);
	while (1)
	{
		line_read = rl_gets();
		if (!line_read)
			break ;
		process_cmd(line_read, &env);
		free(line_read);
		//break ;//one command
	}
	ft_clean_matrix((void **)env);
	rl_clear_history();
	printf("exit\n");
	return (0);
}
