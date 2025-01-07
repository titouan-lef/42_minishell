/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/07 09:59:58 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

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
