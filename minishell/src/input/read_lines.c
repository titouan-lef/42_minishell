/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:21:24 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/10 15:20:48 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
* Goal: Read from stdin whith readline and
*		add the command to the history if not empty.
*
* Return: The read line.
*/
static char	*rl_gets(char **env, int here_doc)
{
	char	*line_read ;
	char	*prompt;

	if (here_doc)
		line_read = readline(" >");
	else
	{
		prompt = get_prompt(env);
		if (!prompt)
			return (NULL);
		line_read = readline(prompt);
		free(prompt);
		if (line_read && *line_read)
			add_history(line_read);
	}
	return (line_read);
}

/*
* Goal: Created a empty command.
*
* Return: 0 on success, 1 on failure.
*/
static int	built_empty_cmd(t_data *data)
{
	free(data->read_lines);
	data->read_lines = (char **)malloc(2 * sizeof(char *));
	if (!data->read_lines)
	{
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (1);
	}
	data->read_lines[0] = ft_strdup("");
	if (!data->read_lines[0])
	{
		free(data->read_lines);
		data->read_lines = NULL;
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
		return (1);
	}
	data->read_lines[1] = NULL;
	return (0);
}

/*
* Goal: Read from stdin whith readline or from last readline.
*
* Return: The read line.
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
		line_read = rl_gets(data->env, here_doc);
		if (!line_read)
			return (NULL);
		data->read_lines = ft_split(line_read, '\n');
		free(line_read);
		if (!data->read_lines)
		{
			ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
			return (NULL);
		}
		if (!data->read_lines[0])
			if (built_empty_cmd(data))
				return (NULL);
	}
	line_read = data->read_lines[i++];
	return (line_read);
}

/*
* Goal: Empty function used to disable readline holding pormpt.
*
* Return: 0.
*/
int	event(void)
{
	return (0);
}
