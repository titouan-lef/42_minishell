/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:30:09 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/28 16:52:33 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
# define TESTER_H

# include <stdlib.h>
# include "minishell.h"
# include "unit_test/unit_test.h"

/*---tests---*/
void	test_echo(char **envp);
void	test_pwd(char **envp);
void	test_lexer();

#endif