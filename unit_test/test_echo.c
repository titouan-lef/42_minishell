/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/15 20:28:01 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "unit_test.h"

int	main(void)
{
	size_t test_number;
	char **cmd;

	start_test("echo");
	cmd = (char **)malloc(sizeof(char *) * 4);
	cmd[0] = "echo";
	cmd[1] = "-n";
	cmd[2] = "Bonjour";
	cmd[3] = NULL;
	test_number = 1;
	assert_equal_out("Bonjour", &echo, cmd, &test_number);
	cmd[1] = "";
	assert_equal_out("Bonjour\n", &echo, cmd, &test_number);
	free(cmd);
	return 0;
}

