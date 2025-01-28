/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/28 20:11:18 by lguerbig         ###   ########.fr       */
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
		case TOKEN_LOGIC_OPE: return "TOKEN_LOGIC_OPE";
		case TOKEN_CMD: return "TOKEN_CMD";
		case TOKEN_NULL: return "TOKEN_NULL";
		default: return "Unknown";
	}
}

void	assert_equal_queue_value(t_queue result, size_t *i, ...)
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
		if (!tokens)
		{
			print_ko(enum_to_str(expected_name), "(null)", i);
			va_end(args);
			queue_clear(&result);
			return ;
		}
		expected_name = (t_token_name)va_arg(args, t_token_name);
		token = tokens->token;
		if (expected_name != token.name)
		{
			print_ko(enum_to_str(expected_name), enum_to_str(token.name), i);
			va_end(args);
			queue_clear(&result);
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
				queue_clear(&result);
				return;
			}
			j++;
		}
		tokens = tokens->next;
		nb_args -= j + 1;
	}
	va_end(args);
	if (tokens)
		print_ko("(null)", enum_to_str(tokens->token.name), i);
	else
		print_ok(i);
	queue_clear(&result);
}

void	assert_equal_queue_redir(t_queue result, size_t *i, ...)
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
		if (!tokens)
		{
			print_ko(enum_to_str(expected_name), "(null)", i);
			va_end(args);
			queue_clear(&result);
			return ;
		}
		expected_name = (t_token_name)va_arg(args, t_token_name);
		token = tokens->token;
		if (expected_name != token.name)
		{
			print_ko(enum_to_str(expected_name), enum_to_str(token.name), i);
			va_end(args);
			queue_clear(&result);
			return;
		}
		j = 0;
		while(token.redir[j])
		{
			expected_value = (char *)va_arg(args, char *);
			if (ft_strcmp(token.redir[j], expected_value))
			{
				print_ko(expected_value, token.redir[j], i);
				va_end(args);
				queue_clear(&result);
				return;
			}
			j++;
		}
		tokens = tokens->next;
		nb_args -= j + 1;
	}
	va_end(args);
	if (tokens)
		print_ko("(null)", enum_to_str(tokens->token.name), i);
	else
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
	queue = tokenizer("echo test");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "test", NULL);

	/*--- test 2 ---*/
	queue = tokenizer("echo   test");;
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "test", NULL);

	/*--- test 3 ---*/
	queue = tokenizer("");
	assert_equal_queue_value(reorganize(&queue), &test_number, NULL);

	/*--- test 4 ---*/
	queue = tokenizer("echo   test   ");
	assert_equal_queue_value(reorganize(&queue),  &test_number, TOKEN_CMD, "echo", "test", NULL);

	/*--- test 5 ---*/
	queue = tokenizer("echo oui && cat non");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "oui", TOKEN_LOGIC_OPE, "&&", TOKEN_CMD, "cat", "non", NULL);

	/*--- test 6 ---*/
	queue = tokenizer("echo oui || cat non");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "oui", TOKEN_LOGIC_OPE, "||", TOKEN_CMD, "cat", "non", NULL);

	/*--- test 7 ---*/
	queue = tokenizer("echo oui | cat non");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "oui", TOKEN_PIPE, "|", TOKEN_CMD, "cat", "non", NULL);

	/*--- test 8 ---*/
	queue = tokenizer("()");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_PAR_OPEN, "(", TOKEN_PAR_CLOSE, ")", NULL);

	/*--- test 9 ---*/
	queue = tokenizer("echo oui && ( 1 || 0 )");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "oui", TOKEN_LOGIC_OPE, "&&", TOKEN_PAR_OPEN, "(", TOKEN_CMD, "1", TOKEN_LOGIC_OPE, "||", TOKEN_CMD, "0", TOKEN_PAR_CLOSE, ")", NULL);

	/*--- test 10 ---*/
	queue = tokenizer("    ");
	assert_equal_queue_value(reorganize(&queue), &test_number, NULL);

	/*--- test 11 ---*/
	queue = tokenizer("echo 'oui && cat non'");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "'oui && cat non'", NULL);

	/*--- test 12 ---*/
	queue = tokenizer("echo \"oui && cat non\"");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "echo", "\"oui && cat non\"", NULL);

	/*--- test 13 ---*/
	queue = tokenizer(">out");
	assert_equal_queue_redir(reorganize(&queue), &test_number, TOKEN_CMD, ">out", NULL);

	/*--- test 14 ---*/
	queue = tokenizer(">out >>oui");
	assert_equal_queue_redir(reorganize(&queue), &test_number, TOKEN_CMD, ">out", ">>oui", NULL);

	/*--- test 15 ---*/
	queue = tokenizer("ls 2>out");
	assert_equal_queue_redir(reorganize(&queue), &test_number, TOKEN_CMD, "2>out",NULL);
	queue = tokenizer("ls 2>out");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "ls", NULL);

	/*--- test 16 ---*/
	queue = tokenizer("ls 2147483648>out");
	assert_equal_queue_redir(reorganize(&queue), &test_number, TOKEN_CMD, ">out", NULL);
	queue = tokenizer("ls 2147483648>out");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "ls", "2147483648", NULL);

	/*--- test 17 ---*/
	queue = tokenizer("cat <in");
	assert_equal_queue_redir(reorganize(&queue), &test_number, TOKEN_CMD, "<in", NULL);
	queue = tokenizer("cat <in");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "cat", NULL);

	/*--- test 18 ---*/
	queue = tokenizer("cat <<here_doc");
	assert_equal_queue_redir(reorganize(&queue), &test_number, TOKEN_CMD, "<<here_doc", NULL);
	queue = tokenizer("cat <<here_doc");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "cat", NULL);

	/*--- test 19 ---*/
	queue = tokenizer("\"echo\"");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "\"echo\"", NULL);

	/*--- test 20 ---*/
	queue = tokenizer("\"echo\" >out");
	assert_equal_queue_redir(reorganize(&queue), &test_number, TOKEN_CMD, ">out", NULL);
	queue = tokenizer("\"echo\" >out");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "\"echo\"", NULL);

	/*--- test 21 ---*/
	queue = tokenizer("\"echo >out\"");
	assert_equal_queue_value(reorganize(&queue), &test_number, TOKEN_CMD, "\"echo >out\"", NULL);
}
