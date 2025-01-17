/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:30:09 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/17 11:20:10 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
# define TESTER_H

# include <stdlib.h>
# include "builtins.h"
# include "commands.h"
# include "tree.h"
# include "redir.h"
# include "unit_test/unit_test.h"

/*---utils---*/
char* enum_to_str(t_token_name token);

/*---special_assert---*/
void	assert_equal_queue(t_queue result, size_t *i, ...);

/*---tests---*/
void	test_echo(char **envp);
void	test_pwd(char **envp);
void	test_tokenizer(void);
void	test_lexer(void);
void	test_tree(void);
void	test_get_tree(void);
void	test_var_expand(char **envp);
void	test_pathname_expand(void);
void	test_quote_removal(void);
void	test_redirs(void);


#endif