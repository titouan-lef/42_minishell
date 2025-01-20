/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/20 16:29:15 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static char **format_cmd(va_list args)
{
	va_list	args_cpy;
	char	**result;
	int		nb_args;
	int		i;

	nb_args = 0;
	va_copy(args_cpy, args);
	while(va_arg(args_cpy, char *))
		++nb_args;
	va_end(args_cpy);
	++nb_args;
	result = (char **)malloc(sizeof(char *) * nb_args);
	if (!result)
		return (NULL);
	i = 0;
	while (i < nb_args)
	{
		result[i] = (char *)va_arg(args, char *);
		i++;
	}
	return (result);
}

static void	run_pwd(char **envp, ...)
{
	char	**split_cmd;
	va_list	args;
	t_out	outputs;

	va_start(args, envp);
	split_cmd = format_cmd(args);
	va_end(args);
	if (!split_cmd)
	{
		perror("malloc failed: run_pwd");
		exit(1);
	}
	redirect_outputs(&outputs);
	pwd();
	set_normal_outputs(&outputs);
	free(split_cmd);
}

void	test_pwd(char **envp)
{
	size_t	test_number;
	char	*pwd;

	start_test("pwd");
	pwd = NULL;
	for (int i = 0; envp[i]; ++i)
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			pwd = envp[i] + 4;
	test_number = 1;

	/*--- test 1 ---*/
	run_pwd(envp, NULL);
	assert_equal_out(pwd, &test_number);

	/*--- test 2 ---*/
	unsetenv("PWD");
	run_pwd(envp, NULL);
	setenv("PWD", pwd, 1);
	assert_equal_out(pwd, &test_number);

}
