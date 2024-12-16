/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/16 16:25:18 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static char **format_cmd(char *arg1, char *arg2, char *arg3)
{
	char **cmd;

	cmd = (char **)malloc(sizeof(char *) * 4);
	cmd[0] = arg1;
	cmd[1] = arg2;
	cmd[2] = arg3;
	cmd[3] = NULL;
	return (cmd);
}

static void	get_result_echo(char **cmd)
{
	t_out	outputs;

	redirect_outputs(&outputs);
	echo(cmd);
	set_normal_outputs(&outputs);
}

void	test_echo()
{
	size_t test_number;
	char **cmd;

	start_test("echo");
	test_number = 1;
	/*--- test 1 ---*/
	cmd = format_cmd("echo", "-n", "Bonjour");
	get_result_echo(cmd);
	assert_equal_out("Bonjour", &test_number);
	free(cmd);

	/*--- test 2 ---*/
	cmd = format_cmd("echo", "", "Bonjour");
	get_result_echo(cmd);
	assert_equal_out("Bonjour\n", &test_number);
	free(cmd);
}

