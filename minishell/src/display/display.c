/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/28 13:36:38 by lguerbig         ###   ########.fr       */
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

int main(void)
{
	char		*line_read ;
	t_queue		tokens;
	t_element	reoganized_tokens;

	while (1)
	{
		line_read = rl_gets();
		if (!line_read)
			break;
		if (*line_read)
		{
			tokens = auto_tokenizer(line_read);
			reoganized_tokens = reorganize(tokens);
		}
		free(line_read);
		if (reoganized_tokens.next == NULL)
			return 1;
	}
	printf("exit\n");
	return (0);
}