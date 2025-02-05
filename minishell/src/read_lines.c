/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:21:24 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/05 12:17:35 by tle-floc         ###   ########.fr       */
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
		free(line_read);
		if (!data->read_lines)
		{
			ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
			return(NULL);
		}
		if (!data->read_lines[i])
		{
			free(data->read_lines);
			data->read_lines = (char **)malloc(2 * sizeof(char *));
			if (!data->read_lines)
			{
				ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
				return(NULL);
			}
			data->read_lines[0] = ft_strdup("");
			if (!data->read_lines[0])
			{
				free(data->read_lines);
				data->read_lines = NULL;
				ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
				return(NULL);
			}
			data->read_lines[1] = NULL;
		}
	}
	line_read = data->read_lines[i++];
	return (line_read);
}