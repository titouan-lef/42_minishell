/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:28:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/11 20:30:40 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	test_echo(envp);
	test_pwd(envp);
	test_tokenizer();
	test_lexer();
	test_tree();
	test_get_tree();
	test_var_expand(envp);
	return (0);
}