/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/17 11:09:14 by lguerbig         ###   ########.fr       */
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

static void	run_echo(char **envp, ...)
{
	char	**split_cmd;
	va_list	args;
	t_out	outputs;

	va_start(args, envp);
	split_cmd = format_cmd(args);
	va_end(args);
	if (!split_cmd)
	{
		perror("malloc failed: run_echo");
		exit(1);
	}
	redirect_outputs(&outputs);
	echo(split_cmd, envp);
	set_normal_outputs(&outputs);
	free(split_cmd);
}

void	test_echo(char **envp)
{
	size_t test_number;

	start_test("echo");
	test_number = 1;

	/*--- test 1 ---*/
	run_echo(envp, "-n", "Bonjour", NULL);
	assert_equal_out("Bonjour", &test_number);

	/*--- test 2 ---*/
	run_echo(envp, "Bonjour", NULL);
	assert_equal_out("Bonjour\n", &test_number);

	/*--- test 3 ---*/
	run_echo(envp, "-n", "-n", "Bonjour", NULL);
	assert_equal_out("Bonjour", &test_number);

	/*--- test 4 ---*/
	run_echo(envp, "-n-n", "Bonjour", NULL);
	assert_equal_out("-n-n Bonjour\n", &test_number);

	/*--- test 5 ---*/
	run_echo(envp, "--n", "Bonjour", NULL);
	assert_equal_out("--n Bonjour\n", &test_number);

	/*--- test 6 ---*/
	run_echo(envp, "-nn", "Bonjour", NULL);
	assert_equal_out("Bonjour", &test_number);

	/*--- test 7 ---*/
	run_echo(envp, "-n", "Bonjour", "-n", NULL);
	assert_equal_out("Bonjour -n", &test_number);

	/*--- test 8 ---*/
	run_echo(envp, "-", "Bonjour", NULL);
	assert_equal_out("- Bonjour\n", &test_number);

	/*--- test 9 ---*/
	run_echo(envp, "--", "Bonjour", NULL);
	assert_equal_out("-- Bonjour\n", &test_number);

	/*--- test 10 ---*/
	run_echo(envp, "-a", "Bonjour", NULL);
	assert_equal_out("-a Bonjour\n", &test_number);

	/*--- test 11 ---*/
	run_echo(envp, "-na", "Bonjour", NULL);
	assert_equal_out("-na Bonjour\n", &test_number);

	/*--- test 12 ---*/
	run_echo(envp, "-n", NULL);
	assert_equal_out("", &test_number);

	/*--- test 13 ---*/
	run_echo(envp, "-nn", NULL);
	assert_equal_out("", &test_number);

	/*--- test 14 ---*/
	run_echo(envp, NULL);
	assert_equal_out("\n", &test_number);

	/*--- test 15 ---*/
	run_echo(envp, "-n", "-", "cequetuveux", NULL);
	assert_equal_out("- cequetuveux", &test_number);
}
