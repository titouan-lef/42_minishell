/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exit_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/02/02 15:38:53 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static void	assert_equal_token_value(t_token token, size_t *i, ...)
{
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
	expected_name = (t_token_name)va_arg(args, t_token_name);
	if (expected_name != token.name)
	{
		print_ko(enum_to_str(expected_name), enum_to_str(token.name), i);
		va_end(args);
		return;
	}
	j = 0;
	while (j < nb_args - 1)
	{
		expected_value = (char *)va_arg(args, char *);
		if (!token.value)
		{
			print_ko(expected_value, "(null)", i);
			va_end(args);
			return ;
		}
		if (!token.value[j])
		{
			print_ko(expected_value, token.value[j], i);
			va_end(args);
			return ;
		}
		if (ft_strcmp(token.value[j], expected_value))
		{
			print_ko(expected_value, token.value[j], i);
			va_end(args);
			return ;
		}
		j++;
	}
	va_end(args);
	if (token.value[j])
		print_ko("(null)", token.value[j], i);
	else
		print_ok(i);
}

static void	assert_equal_token_redir(t_token token, size_t *i, ...)
{
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
	expected_name = (t_token_name)va_arg(args, t_token_name);
	if (expected_name != token.name)
	{
		print_ko(enum_to_str(expected_name), enum_to_str(token.name), i);
		va_end(args);
		return;
	}
	j = 0;
	while (j < nb_args - 1)
	{
		expected_value = (char *)va_arg(args, char *);
		if (!token.redir)
		{
			print_ko(expected_value, "(null)", i);
			va_end(args);
			return ;
		}
		if (!token.redir[j])
		{
			print_ko(expected_value, token.redir[j], i);
			va_end(args);
			return ;
		}
		if (ft_strcmp(token.redir[j], expected_value))
		{
			print_ko(expected_value, token.redir[j], i);
			va_end(args);
			return ;
		}
		j++;
	}
	va_end(args);
	if (token.redir[j])
		print_ko("(null)", token.redir[j], i);
	else
		print_ok(i);
}

void	test_exit_expand(void)
{
	size_t	test_number;
	t_token	token;

	start_test("exit status expansion");
	test_number = 1;

	/*--- test 1 ---*/
	token = token_create(TOKEN_CMD, built_tab("echo", "$?", NULL), NULL);
	expand_exit_status(&token.value, 0);
	assert_equal_token_value(token, &test_number, TOKEN_CMD, "echo", "0", NULL);
	token_clear(token);

	/*--- test 2 ---*/
	token = token_create(TOKEN_CMD, built_tab("echo", "\"$?\"", NULL), NULL);
	expand_exit_status(&token.value, 0);
	assert_equal_token_value(token, &test_number, TOKEN_CMD, "echo", "\"0\"", NULL);
	token_clear(token);

	/*--- test 3 ---*/
	token = token_create(TOKEN_CMD, built_tab("echo", "\'$?\'", NULL), NULL);
	expand_exit_status(&token.value, 0);
	assert_equal_token_value(token, &test_number, TOKEN_CMD, "echo", "\'$?\'", NULL);
	token_clear(token);

	/*--- test 4 ---*/
	token = token_create(TOKEN_CMD, built_tab("echo", "$?", NULL), NULL);
	expand_exit_status(&token.value, 255);
	assert_equal_token_value(token, &test_number, TOKEN_CMD, "echo", "255", NULL);
	token_clear(token);

	/*--- test 5 ---*/
	token = token_create(TOKEN_CMD, built_tab("echo", "$?", NULL), NULL);
	expand_exit_status(&token.value, 1);
	assert_equal_token_value(token, &test_number, TOKEN_CMD, "echo", "1", NULL);
	token_clear(token);

	/*--- test 6 ---*/
	token = token_create(TOKEN_CMD, NULL, built_tab(">$?", NULL));
	expand_exit_status(&token.redir, 0);
	assert_equal_token_redir(token, &test_number, TOKEN_CMD, ">0", NULL);
	token_clear(token);

	/*--- test 7 ---*/
	token = token_create(TOKEN_REDIR, NULL, built_tab(">\"$?\"", NULL));
	expand_exit_status(&token.redir, 0);
	assert_equal_token_redir(token, &test_number, TOKEN_REDIR, ">\"0\"", NULL);
	token_clear(token);

	/*--- test 8 ---*/
	token = token_create(TOKEN_REDIR, NULL, built_tab("<\'$?\'", NULL));
	expand_exit_status(&token.redir, 0);
	assert_equal_token_redir(token, &test_number, TOKEN_REDIR, "<\'$?\'", NULL);
	token_clear(token);

	/*--- test 9 ---*/
	token = token_create(TOKEN_REDIR, NULL, built_tab(">>$?", NULL));
	expand_exit_status(&token.redir, 255);
	assert_equal_token_redir(token, &test_number, TOKEN_REDIR, ">>255", NULL);
	token_clear(token);

	/*--- test 10 ---*/
	token = token_create(TOKEN_REDIR, NULL, built_tab(">$?", NULL));
	expand_exit_status(&token.redir, 1);
	assert_equal_token_redir(token, &test_number, TOKEN_REDIR, ">1", NULL);
	token_clear(token);

	/*--- test 11 ---*/
	token = token_create(TOKEN_REDIR, NULL, built_tab(">\"'$?'\"", NULL));
	expand_exit_status(&token.redir, 0);
	assert_equal_token_redir(token, &test_number, TOKEN_REDIR, ">\"'0'\"", NULL);
	token_clear(token);

	/*--- test 12 ---*/
	token = token_create(TOKEN_REDIR, NULL, built_tab(">'\"$?\"'", NULL));
	expand_exit_status(&token.redir, 0);
	assert_equal_token_redir(token, &test_number, TOKEN_REDIR, ">'\"$?\"'", NULL);
	token_clear(token);

	/*--- test 13 ---*/
	token = token_create(TOKEN_CMD, built_tab("\"'$?'\"", NULL), NULL);
	expand_exit_status(&token.value, 0);
	assert_equal_token_value(token, &test_number, TOKEN_CMD, "\"'0'\"", NULL);
	token_clear(token);

	/*--- test 14 ---*/
	token = token_create(TOKEN_CMD, built_tab("'\"$?\"'", NULL), NULL);
	expand_exit_status(&token.value, 0);
	assert_equal_token_value(token, &test_number, TOKEN_CMD, "'\"$?\"'", NULL);
	token_clear(token);
}
