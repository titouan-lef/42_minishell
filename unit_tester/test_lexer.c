/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/21 15:41:28 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

char* enum_to_str(t_token_name token)
{
	switch (token)
	{
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
	int				j;

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
		j = 0;
		while(token.value[j])
		{
			expected_value = (char *)va_arg(args, char *);
			if (ft_strcmp(token.value[j], expected_value))
			{
				print_ko(expected_value, token.value[j], i);
				va_end(args);
				return;
			}
			j++;
		}
		tokens = tokens->next;
		nb_args -= j + 1;
	}
	va_end(args);
	print_ok(i);
	queue_clear(&result);
}

void	test_lexer(void)
{
	size_t	test_number;
	t_queue	queue;

	start_test("full lexer");
	test_number = 1;

	/*--- test 1 ---*/
	queue = auto_tokenizer("echo test");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "test", NULL);

	/*--- test 2 ---*/
	queue = auto_tokenizer("echo   test");;
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "test", NULL);

	/*--- test 3 ---*/
	queue = auto_tokenizer("");
	assert_equal_queue(reorganize(&queue), &test_number, NULL);

	/*--- test 4 ---*/
	queue = auto_tokenizer("echo   test   ");
	assert_equal_queue(reorganize(&queue),  &test_number, TOKEN_CMD, "echo", "test", NULL);

	/*--- test 5 ---*/
	queue = auto_tokenizer("echo oui && cat non");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "oui", TOKEN_OPE, "&&", TOKEN_CMD, "cat", "non", NULL);

	/*--- test 6 ---*/
	queue = auto_tokenizer("echo oui || cat non");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "oui", TOKEN_OPE, "||", TOKEN_CMD, "cat", "non", NULL);

	/*--- test 7 ---*/
	queue = auto_tokenizer("echo oui | cat non");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "oui", TOKEN_PIPE, "|", TOKEN_CMD, "cat", "non", NULL);

	/*--- test 8 ---*/
	queue = auto_tokenizer("()");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_PAR_OPEN, "(", TOKEN_PAR_CLOSE, ")", NULL);

	/*--- test 9 ---*/
	queue = auto_tokenizer("echo oui && ( 1 || 0 )");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "oui", TOKEN_OPE, "&&", TOKEN_PAR_OPEN, "(", TOKEN_CMD, "1", TOKEN_OPE, "||", TOKEN_CMD, "0", TOKEN_PAR_CLOSE, ")", NULL);

	/*--- test 10 ---*/
	queue = auto_tokenizer("    ");
	assert_equal_queue(reorganize(&queue), &test_number, NULL);

	/*--- test 11 ---*/
	queue = auto_tokenizer("echo 'oui && cat non'");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "'oui && cat non'", NULL);

	/*--- test 12 ---*/
	queue = auto_tokenizer("echo \"oui && cat non\"");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "\"oui && cat non\"", NULL);

	/*--- test 13 ---*/
	queue = auto_tokenizer(">out");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_REDIR, ">out", NULL);

	/*--- test 14 ---*/
	queue = auto_tokenizer(">out >>oui");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_REDIR, ">out", ">>oui", NULL);

	/*--- test 15 ---*/
	queue = auto_tokenizer("ls 2>out");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_REDIR, "2>out", TOKEN_CMD, "ls", NULL);

	/*--- test 16 ---*/
	queue = auto_tokenizer("ls 2147483648>out");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_REDIR, ">out", TOKEN_CMD, "ls", "2147483648", NULL);

	/*--- test 17 ---*/
	queue = auto_tokenizer("cat <in");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_REDIR, "<in", TOKEN_CMD, "cat", NULL);

	/*--- test 18 ---*/
	queue = auto_tokenizer("cat <<here_doc");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_REDIR, "<<here_doc", TOKEN_CMD, "cat", NULL);

	/*--- test 19 ---*/
	queue = auto_tokenizer("\"echo\"");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_CMD, "\"echo\"", NULL);

	/*--- test 20 ---*/
	queue = auto_tokenizer("\"echo\" >out");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_REDIR, ">out", TOKEN_CMD, "\"echo\"", NULL);

	/*--- test 21 ---*/
	queue = auto_tokenizer("\"echo >out\"");
	assert_equal_queue(reorganize(&queue), &test_number, TOKEN_CMD, "\"echo >out\"", NULL);
}
