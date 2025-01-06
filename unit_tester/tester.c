/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:28:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/06 16:47:05 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	test_echo(envp);
	test_pwd(envp);
	test_lexer();
	test_tree();
	return (0);
}