/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/06 19:17:10 by tle-floc         ###   ########.fr       */
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

static int	push_redir_cmd(t_queue *tokens, t_token *cmd)
{
	int	malloc_error;

	malloc_error = 0;
	if (cmd->value || cmd->redir)
	{
		malloc_error = queue_push(tokens, *cmd);
		if (!malloc_error)
		{
			cmd->value = NULL;
			cmd->redir = NULL;
		}
	}
	return (malloc_error);
}

static int	update(t_token *token, t_token *cmd, t_queue *reorganized_tokens)
{
	int	malloc_error;

	malloc_error = 0;
	if (token->name == TOKEN_WORD)
	{
		cmd->value = tab_join_and_free(cmd->value, token->value);
		malloc_error = (cmd->value == NULL);
	}
	else if (token->name == TOKEN_REDIR)
	{
		cmd->redir = tab_join_and_free(cmd->redir, token->value);
		malloc_error = (cmd->redir == NULL);
	}
	if (malloc_error)
		ft_printf_fd(2, "%s: %s\n", NAME, ERR_MALLOC);
	if (token->name != TOKEN_WORD && token->name != TOKEN_REDIR)
	{
		if (push_redir_cmd(reorganized_tokens, cmd))
			malloc_error = 1;
		if (queue_push(reorganized_tokens, *token))
			malloc_error = 1;
	}
	return (malloc_error);
}

static t_queue	form_cmd(t_queue *tokens)
{
	t_queue	reorganized_tokens;
	t_token	token;
	t_token	cmd;

	cmd = token_create(TOKEN_CMD, NULL, NULL);
	reorganized_tokens = queue_create();
	while (!queue_is_empty(tokens))
	{
		token = queue_pop(tokens);
		if (update(&token, &cmd, &reorganized_tokens))
		{
			token_clear(cmd);
			queue_clear(tokens);
			queue_clear(&reorganized_tokens);
			return (reorganized_tokens);
		}
	}
	if (push_redir_cmd(&reorganized_tokens, &cmd))
		queue_clear(&reorganized_tokens);
	return (reorganized_tokens);
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
	lexer("echo test", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "echo", "test", NULL);

	/*--- test 2 ---*/
	lexer("echo   test", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "echo", "test", NULL);

	/*--- test 3 ---*/
	lexer("", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, NULL);

	/*--- test 4 ---*/
	lexer("echo   test   ", &queue);
	assert_equal_queue_value(form_cmd(&queue),  &test_number, TOKEN_CMD, "echo", "test", NULL);

	/*--- test 5 ---*/
	lexer("echo oui && cat non", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "echo", "oui", TOKEN_LOGIC_OPE, "&&", TOKEN_CMD, "cat", "non", NULL);

	/*--- test 6 ---*/
	lexer("echo oui || cat non", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "echo", "oui", TOKEN_LOGIC_OPE, "||", TOKEN_CMD, "cat", "non", NULL);

	/*--- test 7 ---*/
	lexer("echo oui | cat non", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "echo", "oui", TOKEN_PIPE, "|", TOKEN_CMD, "cat", "non", NULL);

	/*--- test 8 ---*/
	lexer("()", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_PAR_OPEN, "(", TOKEN_PAR_CLOSE, ")", NULL);

	/*--- test 9 ---*/
	lexer("echo oui && ( 1 || 0 )", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "echo", "oui", TOKEN_LOGIC_OPE, "&&", TOKEN_PAR_OPEN, "(", TOKEN_CMD, "1", TOKEN_LOGIC_OPE, "||", TOKEN_CMD, "0", TOKEN_PAR_CLOSE, ")", NULL);

	/*--- test 10 ---*/
	lexer("    ", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, NULL);

	/*--- test 11 ---*/
	lexer("echo 'oui && cat non'", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "echo", "'oui && cat non'", NULL);

	/*--- test 12 ---*/
	lexer("echo \"oui && cat non\"", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "echo", "\"oui && cat non\"", NULL);

	/*--- test 13 ---*/
	lexer(">out", &queue);
	assert_equal_queue_redir(form_cmd(&queue), &test_number, TOKEN_CMD, ">out", NULL);

	/*--- test 14 ---*/
	lexer(">out >>oui", &queue);
	assert_equal_queue_redir(form_cmd(&queue), &test_number, TOKEN_CMD, ">out", ">>oui", NULL);

	/*--- test 15 ---*/
	lexer("ls 2>out", &queue);
	assert_equal_queue_redir(form_cmd(&queue), &test_number, TOKEN_CMD, "2>out",NULL);
	lexer("ls 2>out", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "ls", NULL);

	/*--- test 16 ---*/
	lexer("ls 2147483648>out", &queue);
	assert_equal_queue_redir(form_cmd(&queue), &test_number, TOKEN_CMD, ">out", NULL);
	lexer("ls 2147483648>out", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "ls", "2147483648", NULL);

	/*--- test 17 ---*/
	lexer("cat <in", &queue);
	assert_equal_queue_redir(form_cmd(&queue), &test_number, TOKEN_CMD, "<in", NULL);
	lexer("cat <in", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "cat", NULL);

	/*--- test 18 ---*/
	lexer("cat <<here_doc", &queue);
	assert_equal_queue_redir(form_cmd(&queue), &test_number, TOKEN_CMD, "<<here_doc", NULL);
	lexer("cat <<here_doc", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "cat", NULL);

	/*--- test 19 ---*/
	lexer("\"echo\"", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "\"echo\"", NULL);

	/*--- test 20 ---*/
	lexer("\"echo\" >out", &queue);
	assert_equal_queue_redir(form_cmd(&queue), &test_number, TOKEN_CMD, ">out", NULL);
	lexer("\"echo\" >out", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "\"echo\"", NULL);

	/*--- test 21 ---*/
	lexer("\"echo >out\"", &queue);
	assert_equal_queue_value(form_cmd(&queue), &test_number, TOKEN_CMD, "\"echo >out\"", NULL);
}
