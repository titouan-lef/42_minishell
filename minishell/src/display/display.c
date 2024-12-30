/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/30 03:27:56 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

char *rl_gets()
{
	char	*line_read ;

	line_read = readline("$");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

void print_tokens(t_element *tokens)
{
	int	i;

	while(tokens)
	{
		printf("%d | ", tokens->token.name);
		i = 0;
		while (tokens->token.value[i])
			printf("'%s' ", tokens->token.value[i++]);
		printf("\n");
		tokens = tokens->next;
	}
}

int main(void)
{
	char		*line_read ;
	t_queue		tokens;
	t_element	*reorganized_tokens = NULL;

	while (1)
	{
		line_read = rl_gets();
		if (!line_read)
			break;
		if (*line_read)
		{
			tokens = auto_tokenizer(line_read);
			reorganized_tokens = reorganize(tokens);
			print_tokens(reorganized_tokens);
		}
		free(line_read);
		if (reorganized_tokens == NULL)
			continue;
	}
	printf("exit\n");
	return (0);
}