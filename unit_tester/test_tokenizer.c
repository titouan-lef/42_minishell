/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/06 19:13:24 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

void	test_tokenizer(void)
{
	size_t	test_number;
	t_out	outs;
	t_queue	queue;

	start_test("lexer");
	test_number = 1;

	/*--- test 1 ---*/
	lexer("echo test", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "test", NULL);

	/*--- test 2 ---*/
	lexer("echo   test", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "test", NULL);

	/*--- test 3 ---*/
	lexer("", &queue);
	assert_equal_queue_value(queue, &test_number, NULL);

	/*--- test 4 ---*/
	lexer("echo   test   ", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "test", NULL);

	/*--- test 5 ---*/
	lexer("echo oui && cat non", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "oui", TOKEN_LOGIC_OPE, "&&", TOKEN_WORD, "cat", TOKEN_WORD, "non", NULL);

	/*--- test 6 ---*/
	lexer("echo oui || cat non", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "oui", TOKEN_LOGIC_OPE, "||", TOKEN_WORD, "cat", TOKEN_WORD, "non", NULL);

	/*--- test 7 ---*/
	lexer("echo oui | cat non", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "oui", TOKEN_PIPE, "|", TOKEN_WORD, "cat", TOKEN_WORD, "non", NULL);

	/*--- test 8 ---*/
	lexer("()", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_PAR_OPEN, "(", TOKEN_PAR_CLOSE, ")", NULL);

	/*--- test 9 ---*/
	lexer("echo oui && ( 1 || 0 )", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "oui", TOKEN_LOGIC_OPE, "&&", TOKEN_PAR_OPEN, "(", TOKEN_WORD, "1", TOKEN_LOGIC_OPE, "||", TOKEN_WORD, "0", TOKEN_PAR_CLOSE, ")", NULL);

	/*--- test 10 ---*/
	lexer("    ", &queue);
	assert_equal_queue_value(queue, &test_number, NULL);

	/*--- test 11 ---*/
	lexer("echo 'oui && cat non'", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "'oui && cat non'", NULL);

	/*--- test 12 ---*/
	lexer("echo \"oui && cat non\"", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "\"oui && cat non\"", NULL);

	fflush(stdout);
	/*--- test 13 ---*/
	lexer(">out", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_REDIR, ">out", NULL);

	/*--- test 14 ---*/
	lexer(">out >>oui", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_REDIR, ">out", TOKEN_REDIR, ">>oui", NULL);

	/*--- test 15 ---*/
	lexer("ls 2>out", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "ls", TOKEN_REDIR, "2>out", NULL);

	/*--- test 16 ---*/
	lexer("ls 2147483648>out", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "ls", TOKEN_WORD, "2147483648", TOKEN_REDIR, ">out", NULL);

	/*--- test 17 ---*/
	lexer("cat <in", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "cat", TOKEN_REDIR, "<in", NULL);

	/*--- test 18 ---*/
	lexer("cat <<here_doc", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "cat", TOKEN_REDIR, "<<here_doc", NULL);

	/*--- test 19 ---*/
	lexer("\"echo\"", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "\"echo\"", NULL);

	/*--- test 20 ---*/
	lexer("\"echo\" >out", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "\"echo\"", TOKEN_REDIR, ">out", NULL);

	/*--- test 21 ---*/
	lexer("\"echo >out\"", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "\"echo >out\"", NULL);

	/*--- test 22 && 23 ---*/
	redirect_outputs(&outs);
	t_queue	result;
	lexer("echo >'out", &result);
	set_normal_outputs(&outs);
	assert_equal_queue_value(result, &test_number, NULL);
	assert_equal_err("minishell: syntax error: unclosed quote `''\n", &test_number);

	/*--- test 24 ---*/
	lexer("echo >", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_REDIR, ">", NULL);

	/*--- test 25 ---*/
	lexer("echo <", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_REDIR, "<", NULL);

	/*--- test 26 ---*/
	lexer("echo >>", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_REDIR, ">>", NULL);

	/*--- test 27 ---*/
	lexer("echo <<", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_REDIR, "<<", NULL);

	/*--- test 28---*/
	lexer("echo > && echo oui", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_REDIR, ">", TOKEN_LOGIC_OPE, "&&", TOKEN_WORD, "echo", TOKEN_WORD, "oui", NULL);

	/*--- test 29 && 30 ---*/
	redirect_outputs(&outs);
	lexer("echo >' && echo oui", &result);
	set_normal_outputs(&outs);
	assert_equal_queue_value(result, &test_number, NULL);
	assert_equal_err("minishell: syntax error: unclosed quote `''\n", &test_number);

	/*--- test 31 ---*/
	lexer("echo >>&&", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_REDIR, ">>", TOKEN_LOGIC_OPE, "&&", NULL);

	/*--- test 32 ---*/
	lexer("echo oui&", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "oui&", NULL);

	/*--- test 33 ---*/
	lexer("echo &oui", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "&oui", NULL);

	/*--- test 34 ---*/
	lexer("echo oui &", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "oui", TOKEN_WORD, "&", NULL);

	/*--- test 35 ---*/
	lexer("echo & oui", &queue);
	assert_equal_queue_value(queue, &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "&", TOKEN_WORD, "oui", NULL);
}
