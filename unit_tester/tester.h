/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:30:09 by lguerbig          #+#    #+#             */
/*   Updated: 2024/12/17 13:28:08 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
# define TESTER_H

# include <stdlib.h>
# include "builtins.h"
# include "unit_test/unit_test.h"

/*---tests---*/
void	test_echo(char **envp);
void	test_pwd(char **envp);

#endif