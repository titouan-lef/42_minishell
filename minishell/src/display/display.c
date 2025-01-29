/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/29 16:08:18 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "builtins.h"

char	*rl_gets(char **env)
{
	char	*line_read ;
	char	*prompt;

	prompt = get_prompt(env);
	line_read = readline(prompt);
	free(prompt);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

void	print_tokens(t_queue *tokens) //remove at the end, only needed for debug
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

static char	*rebase_pwd(char *pwd, char **env)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	if (!pwd)
		return (NULL);
	while (env[i])
		if (ft_strncmp("HOME=", env[i++], 5) == 0)
			break ;
	if (env[i--] != NULL)
	{
		if (ft_strncmp(pwd, env[i] + 5, ft_strlen(env[i] + 5)) == 0)
		{
			result = ft_strjoin("~", pwd + ft_strlen(env[i] + 5));
			free(pwd);
		}
		return (result);
	}
	return (pwd);
}

static char	*color_pwd(char *pwd)
{
	static unsigned char	color = 0;
	char					*new_pwd;
	char					*tmp;

	tmp = ft_itoa(color);
	new_pwd = ft_strjoin("\1\e[38;5;", tmp);
	free(tmp);
	tmp = ft_strjoin(new_pwd, "m\2");
	free (new_pwd);
	new_pwd = ft_strjoin(tmp, pwd);
	free(tmp);
	free(pwd);
	tmp = ft_strjoin(new_pwd, "\1\e[0m\2");
	free(new_pwd);
	color += 3;
	return (tmp);
}

char	*get_prompt(char **env)
{
	char	*pwd;
	char	*prompt;
	char	*tmp;

	pwd = get_cwd(env);
	pwd = rebase_pwd(pwd, env);
	pwd = color_pwd(pwd);
	prompt = ft_strjoin(NAME, ":");
	tmp = ft_strjoin(prompt, pwd);
	free(pwd);
	free(prompt);
	prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	if (!prompt)
		return ("minishell$ ");
	return (prompt);
}
