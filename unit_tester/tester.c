/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:28:01 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/16 19:53:02 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	test_echo(envp);
	return (0);
}