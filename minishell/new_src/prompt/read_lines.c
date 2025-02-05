/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:21:24 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/05 17:22:42 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

static char	*rl_gets(char **env)
{
	char	*line_read ;
	char	*prompt;

	prompt = get_prompt(env);
	if (!prompt)
		return (NULL);
	line_read = readline(prompt);
	free(prompt);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

/*
* Goal: Read from stdin whith readline or from last readline.
*
* Return: The line read with readline or from last read.
*
* Warning: data must not be null.
*/
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