/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:30:09 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/11 14:28:55 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
# define TESTER_H

# include <stdlib.h>
# include "builtins.h"
# include "commands.h"
# include "tree.h"
# include "unit_test/unit_test.h"

/*---tests---*/
void	test_echo(char **envp);
void	test_pwd(char **envp);
void	test_tokenizer(void);
void	test_lexer(void);
void	test_tree(void);
void	test_get_tree(void);

#endif