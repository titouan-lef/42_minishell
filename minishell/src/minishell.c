/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:34:29 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/21 16:43:18 by tle-floc         ###   ########.fr       */
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

	if (*input)
	{
		tokens = auto_tokenizer(input);
		reorganized_tokens = reorganize(&tokens);
		make_execution(&reorganized_tokens, env);
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
