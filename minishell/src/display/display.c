/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/04 19:28:16 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

char	*rl_gets(void)
{
	char	*line_read ;

	line_read = readline("$");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

void	print_tokens(t_queue *tokens)
{
	t_element	*list;
	int			i;

	list = tokens->head;
	while (list)
	{
		printf("%d | ", list->token.name);
		i = 0;
		while (list->token.value[i])
			printf("'%s' ", list->token.value[i++]);
		printf("\n");
		list = list->next;
	}
}

int	main(int argc, char **argv, char**envp)
{
	char		*line_read ;
	t_queue		tokens;
	t_queue		reorganized_tokens;

	(void)argc;
	(void)argv;
	while (1)
	{
		line_read = rl_gets();
		if (!line_read)
			break ;
		if (*line_read)
		{
			tokens = auto_tokenizer(line_read);
			reorganized_tokens = reorganize(tokens);
			replace_env_var(&reorganized_tokens, envp);
			print_tokens(&reorganized_tokens);
			queue_clear(&reorganized_tokens);
		}
		else
			reorganized_tokens = queue_create();
		free(line_read);
		(void)reorganized_tokens;
		if (reorganized_tokens.head == NULL)
			continue ;
	}
	printf("exit\n");
	return (0);
}
