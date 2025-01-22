/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/22 22:43:13 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

void	test_tokenizer(void)
{
	size_t	test_number;
	t_out	outs;

	start_test("tokenizer");
	test_number = 1;

	/*--- test 1 ---*/
	assert_equal_queue(tokenizer("echo test"), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "test", NULL);

	/*--- test 2 ---*/
	assert_equal_queue(tokenizer("echo   test"), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "test", NULL);

	/*--- test 3 ---*/
	assert_equal_queue(tokenizer(""), &test_number, NULL);

	/*--- test 4 ---*/
	assert_equal_queue(tokenizer("echo   test   "), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "test", NULL);

	/*--- test 5 ---*/
	assert_equal_queue(tokenizer("echo oui && cat non"), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "oui", TOKEN_LOGIC_OPE, "&&", TOKEN_WORD, "cat", TOKEN_WORD, "non", NULL);

	/*--- test 6 ---*/
	assert_equal_queue(tokenizer("echo oui || cat non"), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "oui", TOKEN_LOGIC_OPE, "||", TOKEN_WORD, "cat", TOKEN_WORD, "non", NULL);

	/*--- test 7 ---*/
	assert_equal_queue(tokenizer("echo oui | cat non"), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "oui", TOKEN_PIPE, "|", TOKEN_WORD, "cat", TOKEN_WORD, "non", NULL);

	/*--- test 8 ---*/
	assert_equal_queue(tokenizer("()"), &test_number, TOKEN_PAR_OPEN, "(", TOKEN_PAR_CLOSE, ")", NULL);

	/*--- test 9 ---*/
	assert_equal_queue(tokenizer("echo oui && ( 1 || 0 )"), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "oui", TOKEN_LOGIC_OPE, "&&", TOKEN_PAR_OPEN, "(", TOKEN_WORD, "1", TOKEN_LOGIC_OPE, "||", TOKEN_WORD, "0", TOKEN_PAR_CLOSE, ")", NULL);

	/*--- test 10 ---*/
	assert_equal_queue(tokenizer("    "), &test_number, NULL);

	/*--- test 11 ---*/
	assert_equal_queue(tokenizer("echo 'oui && cat non'"), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "'oui && cat non'", NULL);

	/*--- test 12 ---*/
	assert_equal_queue(tokenizer("echo \"oui && cat non\""), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "\"oui && cat non\"", NULL);

	/*--- test 13 ---*/
	assert_equal_queue(tokenizer(">out"), &test_number, TOKEN_REDIR, ">out", NULL);

	/*--- test 14 ---*/
	assert_equal_queue(tokenizer(">out >>oui"), &test_number, TOKEN_REDIR, ">out", TOKEN_REDIR, ">>oui", NULL);

	/*--- test 15 ---*/
	assert_equal_queue(tokenizer("ls 2>out"), &test_number, TOKEN_WORD, "ls", TOKEN_REDIR, "2>out", NULL);

	/*--- test 16 ---*/
	assert_equal_queue(tokenizer("ls 2147483648>out"), &test_number, TOKEN_WORD, "ls", TOKEN_WORD, "2147483648", TOKEN_REDIR, ">out", NULL);

	/*--- test 17 ---*/
	assert_equal_queue(tokenizer("cat <in"), &test_number, TOKEN_WORD, "cat", TOKEN_REDIR, "<in", NULL);

	/*--- test 18 ---*/
	assert_equal_queue(tokenizer("cat <<here_doc"), &test_number, TOKEN_WORD, "cat", TOKEN_REDIR, "<<here_doc", NULL);

	/*--- test 19 ---*/
	assert_equal_queue(tokenizer("\"echo\""), &test_number, TOKEN_WORD, "\"echo\"", NULL);

	/*--- test 20 ---*/
	assert_equal_queue(tokenizer("\"echo\" >out"), &test_number, TOKEN_WORD, "\"echo\"", TOKEN_REDIR, ">out", NULL);

	/*--- test 21 ---*/
	assert_equal_queue(tokenizer("\"echo >out\""), &test_number, TOKEN_WORD, "\"echo >out\"", NULL);

	/*--- test 22 && 23 ---*/
	redirect_outputs(&outs);
	t_queue result = tokenizer("echo >'out");
	set_normal_outputs(&outs);
	assert_equal_queue(result, &test_number, NULL);
	assert_equal_err("minishell: syntax error: unclosed quote `''\n", &test_number);

	/*--- test 24 ---*/
	assert_equal_queue(tokenizer("echo >"), &test_number, TOKEN_WORD, "echo", TOKEN_REDIR, ">", NULL);

	/*--- test 25 ---*/
	assert_equal_queue(tokenizer("echo <"), &test_number, TOKEN_WORD, "echo", TOKEN_REDIR, "<", NULL);

	/*--- test 26 ---*/
	assert_equal_queue(tokenizer("echo >>"), &test_number, TOKEN_WORD, "echo", TOKEN_REDIR, ">>", NULL);

	/*--- test 27 ---*/
	assert_equal_queue(tokenizer("echo <<"), &test_number, TOKEN_WORD, "echo", TOKEN_REDIR, "<<", NULL);

	/*--- test 28---*/
	assert_equal_queue(tokenizer("echo > && echo oui"), &test_number, TOKEN_WORD, "echo", TOKEN_REDIR, ">", TOKEN_LOGIC_OPE, "&&", TOKEN_WORD, "echo", TOKEN_WORD, "oui", NULL);

	/*--- test 29 && 30 ---*/
	redirect_outputs(&outs);
	result = tokenizer("echo >' && echo oui");
	set_normal_outputs(&outs);
	assert_equal_queue(result, &test_number, NULL);
	assert_equal_err("minishell: syntax error: unclosed quote `''\n", &test_number);
}
