/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:28:01 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/28 16:51:44 by lguerbig         ###   ########.fr       */
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
	return (0);
}