/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/08 18:50:45 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static char* enum_to_str(t_token_name token) {
	switch (token) {
		case TOKEN_PIPE: return "TOKEN_PIPE";
		case TOKEN_PAR_OPEN: return "TOKEN_PAR_OPEN";
		case TOKEN_PAR_CLOSE: return "TOKEN_PAR_OPEN";
		case TOKEN_WORD: return "TOKEN_WORD";
		case TOKEN_REDIR: return "TOKEN_REDIR";
		case TOKEN_OPE: return "TOKEN_OPE";
		case TOKEN_CMD: return "TOKEN_CMD";
		case TOKEN_NULL: return "TOKEN_NULL";
		default: return "Unknown";
	}
}

void	assert_equal_queue(t_queue result, size_t *i, ...)
{
	t_element		*tokens;
	t_token			token;
	char			*expected_value;
	t_token_name	expected_name;
	va_list			args;
	va_list			args_cpy;
	int				nb_args;

	va_start(args, i);
	nb_args = 0;
	va_copy(args_cpy, args);
	while(va_arg(args_cpy, char *))
		++nb_args;
	va_end(args_cpy);
	tokens = result.head;
	while (nb_args > 0)
	{
		expected_name = (t_token_name)va_arg(args, t_token_name);
		if (!tokens)
		{
			print_ko(enum_to_str(expected_name), "", i);
			va_end(args);
			return ;
		}
		token = tokens->token;
		if (expected_name != token.name)
		{
			print_ko(enum_to_str(expected_name), enum_to_str(token.name), i);
			va_end(args);
			return;
		}
		expected_value = (char *)va_arg(args, char *);
		if (ft_strcmp(token.value[0], expected_value))
		{
			print_ko(expected_value, token.value[0], i);
			va_end(args);
			return;
		}
		tokens = tokens->next;
		nb_args -= 2;
	}
	va_end(args);
	print_ok(i);
	queue_clear(&result);
}

void	test_lexer()
{
	size_t	test_number;

	start_test("lexer");
	test_number = 1;

	/*--- test 1 ---*/
	assert_equal_queue(auto_tokenizer("echo test"), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "test", NULL);

	/*--- test 2 ---*/
	assert_equal_queue(auto_tokenizer("echo   test"), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "test", NULL);

	/*--- test 3 ---*/
	assert_equal_queue(auto_tokenizer(""), &test_number, NULL);

	/*--- test 4 ---*/
	assert_equal_queue(auto_tokenizer("echo   test   "), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "test", NULL);

	/*--- test 5 ---*/
	assert_equal_queue(auto_tokenizer("echo oui && cat non"), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "oui", TOKEN_OPE, "&&", TOKEN_WORD, "cat", TOKEN_WORD, "non", NULL);

	/*--- test 6 ---*/
	assert_equal_queue(auto_tokenizer("echo oui || cat non"), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "oui", TOKEN_OPE, "||", TOKEN_WORD, "cat", TOKEN_WORD, "non", NULL);

	/*--- test 7 ---*/
	assert_equal_queue(auto_tokenizer("echo oui | cat non"), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "oui", TOKEN_PIPE, "|", TOKEN_WORD, "cat", TOKEN_WORD, "non", NULL);

	/*--- test 8 ---*/
	assert_equal_queue(auto_tokenizer("()"), &test_number, TOKEN_PAR_OPEN, "(", TOKEN_PAR_CLOSE, ")", NULL);

	/*--- test 9 ---*/
	assert_equal_queue(auto_tokenizer("echo oui && ( 1 || 0 )"), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "oui", TOKEN_OPE, "&&", TOKEN_PAR_OPEN, "(", TOKEN_WORD, "1", TOKEN_OPE, "||", TOKEN_WORD, "0", TOKEN_PAR_CLOSE, ")", NULL);

	/*--- test 10 ---*/
	assert_equal_queue(auto_tokenizer("    "), &test_number, NULL);

	/*--- test 11 ---*/
	assert_equal_queue(auto_tokenizer("echo 'oui && cat non'"), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "'oui && cat non'", NULL);

	/*--- test 12 ---*/
	assert_equal_queue(auto_tokenizer("echo \"oui && cat non\""), &test_number, TOKEN_WORD, "echo", TOKEN_WORD, "\"oui && cat non\"", NULL);

}
