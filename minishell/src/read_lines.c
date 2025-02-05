/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:21:24 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/05 11:23:36 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

char	*read_lines(t_data *data, int here_doc)
{
	char		*line_read;
	static int	i = 0;

	if (!data->read_lines || !data->read_lines[i])
	{
		if (data->read_lines)
			ft_clean_matrix((void **)data->read_lines);
		data->read_lines = NULL;
		i = 0;
		if (here_doc)
			line_read = readline("> ");
		else
			line_read = rl_gets(data->env);
		if (!line_read)
			return (NULL);
		data->read_lines = ft_split(line_read, '\n');
		if (!data->read_lines)
		{
			ft_printf_fd(2, "%s: %S\n", NAME, ERR_MALLOC);
			return(NULL);
		}
		free(line_read);
	}
	line_read = data->read_lines[i++];
	return (line_read);
}