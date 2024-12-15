/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/15 11:57:31 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "unit_test.h"

int main(int argc, const char *argv[])
{
	t_out outputs;

	redirect_outputs(&outputs);

	puts("doing an ls or something now");

	set_normal_outputs(&outputs);

	puts("back to normal output");

	return 0;
}

